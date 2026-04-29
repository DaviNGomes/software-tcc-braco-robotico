from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QMessageBox, QFileDialog
import sys
import re
import serial
import threading
import time
from serial.tools import list_ports
from uiInterfaceTCCCores import Ui_MainWindow

# Classe para comunicação com o Arduino
class LeitorSerialArduinoTCC(threading.Thread):
    def __init__(self, porta, baudrate=9600):
        super().__init__()
        self.porta = porta
        self.baudrate = baudrate
        self.arduino = None
        self.running = True
        self.conectado = False
        self.lock = threading.Lock()

    def run(self):
        if not self.porta:
            print("[INFO] Nenhuma porta definida, executando sem conexão com o Arduino.")
            return
        try:
            self.arduino = serial.Serial(self.porta, self.baudrate, timeout=1)
            time.sleep(2)
            self.conectado = True
            print(f"[SUCESSO] Conectado ao Arduino na porta {self.porta}")
        except Exception as e:
            print(f"[ERRO] Falha ao conectar ao Arduino na porta {self.porta}: {e}")

    def enviar_comando(self, comando):
        if self.arduino and self.arduino.is_open:
            try:
                self.arduino.write((comando + "\n").encode())
                print(f"[ENVIADO] {comando}")
            except Exception as e:
                print(f"[ERRO] Ao enviar comando: {e}")

    def parar(self):
        self.running = False
        if self.arduino and self.arduino.is_open:
            self.arduino.close()
            print("[INFO] Conexão com Arduino encerrada.")

# Função para listar as portas
def listar_portas():
    return [porta.device for porta in list_ports.comports()]

# Classe principal da interface
class InterfaceTCC(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.leitor = None
        self.arquivo_log = None
        self.modo_manual_ativo = False
        self.leitor = None

        # Adiciona portas disponíveis no comboBox
        self.ui.comboBox.addItem("Nenhuma porta (modo simulado)")
        self.ui.comboBox.addItems(listar_portas())

        # Conecta botões
        self.ui.btn_conectar.clicked.connect(self.conectar_arduino)
        self.ui.pushButton_3.clicked.connect(self.pagmanual)
        self.ui.pushButton_4.clicked.connect(self.pagaut)
        self.ui.btn_sobre.clicked.connect(self.sobre)
        self.ui.btn_voltar.clicked.connect(self.escolha)
        self.ui.btn_voltar2.clicked.connect(self.escolha)
        self.ui.btn_voltar3.clicked.connect(self.pagaut)
        self.ui.btn_voltar4.clicked.connect(self.paginicial)
        self.ui.btn_voltarINICIO.clicked.connect(self.paginicial)
        self.ui.btn_ajuda.clicked.connect(self.ajuda)
        self.ui.btn_executar.clicked.connect(self.executar_comandos)
        self.ui.btn_salvar.clicked.connect(self.salvar)
        self.ui.btn_carregar.clicked.connect(self.carregar)

        # Botões de controle do motor
        self.ui.btn_linhaEsquerda.pressed.connect(self.Esquerda)
        self.ui.btn_linhaEsquerda.released.connect(self.pararlinha)

        self.ui.btn_linhaDireita.pressed.connect(self.Direita)
        self.ui.btn_linhaDireita.released.connect(self.pararlinha)

        self.ui.btn_baseHora.pressed.connect(self.avancarbase_motor)
        self.ui.btn_baseHora.released.connect(self.pararB_motor)

        self.ui.btn_baseAntiHora.pressed.connect(self.recuarbase_motor)
        self.ui.btn_baseAntiHora.released.connect(self.pararB_motor)

        self.ui.btn_ombroFrente.pressed.connect(self.avancarO_motor)
        self.ui.btn_ombroFrente.released.connect(self.pararO_motor)

        self.ui.btn_ombroTras.pressed.connect(self.recuarO_motor)
        self.ui.btn_ombroTras.released.connect(self.pararO_motor)

        self.ui.btn_cotoveloFrente.pressed.connect(self.avancarC_motor)
        self.ui.btn_cotoveloFrente.released.connect(self.pararC_motor)

        self.ui.btn_cotoveloTras.pressed.connect(self.recuarC_motor)
        self.ui.btn_cotoveloTras.released.connect(self.pararC_motor)

        self.ui.btn_pulsoFrente.pressed.connect(self.avancarMP_motor)
        self.ui.btn_pulsoTras.pressed.connect(self.recuarMP_motor)
        self.ui.btn_pulsoFrente.released.connect(self.pararMP_motor)
        self.ui.btn_pulsoTras.released.connect(self.pararMP_motor)

        self.ui.btn_pulsoHora.pressed.connect(self.avancarGP_motor)
        self.ui.btn_pulsoAntiHora.pressed.connect(self.recuarGP_motor)
        self.ui.btn_pulsoHora.released.connect(self.pararGP_motor)
        self.ui.btn_pulsoAntiHora.released.connect(self.pararGP_motor)

        self.ui.btn_garraAbrir.pressed.connect(self.abrirG_motor)
        self.ui.btn_garraFechar.pressed.connect(self.fecharG_motor)
        self.ui.btn_garraAbrir.released.connect(self.pararG_motor)
        self.ui.btn_garraFechar.released.connect(self.pararG_motor)

        self.ui.btn_resetar.clicked.connect(self.resetar)

    def conectar_arduino(self):
        texto_combo = self.ui.comboBox.currentText()
        if "Nenhuma" in texto_combo or not texto_combo:
            QMessageBox.information(self, "Modo Simulado", "Continuando sem conexão com o Arduino.")
            self.ui.stackedWidget.setCurrentIndex(1)
            return

        self.porta = texto_combo.split(" - ")[0]
        self.leitor = LeitorSerialArduinoTCC(porta=self.porta)
        self.leitor.start()

        time.sleep(2.2)
        if self.leitor.conectado:
            QMessageBox.information(self, "Conexão", f"Conectado ao Arduino na porta {self.porta}")
        else:
            QMessageBox.warning(self, "Aviso", "Não foi possível conectar ao Arduino.")

        self.ui.stackedWidget.setCurrentIndex(1)

    def registrar_posicao(self):
        if not (self.modo_manual_ativo and self.leitor and self.leitor.conectado):
            return
        try:
            # espera pequena pra garantir que Arduino mandou algo
            #time.sleep(0.1)
            if self.leitor.arduino.in_waiting > 0:
                linha = self.leitor.arduino.readline().decode(errors='ignore').strip()
                self.arquivo_log.write(linha + "\n")
                self.arquivo_log.flush()
                print(f"[LOG] {linha}")
        except Exception as e:
            print(f"[ERRO] Falha ao registrar posição: {e}")

    def pagmanual(self):
        import datetime
        self.ui.stackedWidget.setCurrentIndex(2)
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("MODO_MANUAL")
        # Cria o arquivo de log com data e hora
        nome_arquivo = datetime.datetime.now().strftime("registro_%Y-%m-%d_%H-%M-%S.txt")
        self.arquivo_log = open(nome_arquivo, "a", encoding="utf-8")
        self.modo_manual_ativo = True
        print(f"[LOG] Arquivo criado: {nome_arquivo}")

    def pagaut(self):
        self.ui.stackedWidget.setCurrentIndex(3)
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("MODO_AUTOMATICO")  # define ok = 2 no Arduino
        #fecha o arquivo
        if self.modo_manual_ativo and self.arquivo_log:
            self.arquivo_log.close()
            self.arquivo_log = None
            self.modo_manual_ativo = False
            print("[LOG] Arquivo de log fechado.")

    def Esquerda(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("ESQUERDA")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")
    
    def Direita(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("DIREITA")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")


    def avancarbase_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("AVANCARB")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def avancarO_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("AVANCARO")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def avancarC_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("AVANCARC")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")
    
    def avancarMP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("AVANCARMP")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def avancarGP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("AVANCARGP")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def abrirG_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("ABRIRG")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def recuarbase_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RECUARB")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def recuarO_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RECUARO")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")
    
    def recuarC_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RECUARC")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def recuarMP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RECUARMP")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def recuarGP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RECUARGP")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def fecharG_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("FECHARG")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")

    def resetar (self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("RESETAR")
        else:
            QMessageBox.warning(self, "Erro", "Arduino não conectado.")        
            
    def pararB_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARB")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararO_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARO")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararC_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARC")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararMP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARMP")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararGP_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARGP")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararG_motor(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARG")
            time.sleep(0.1)
            self.registrar_posicao()

    def pararlinha(self):
        if self.leitor and self.leitor.conectado:
            self.leitor.enviar_comando("PARARL")

    def executar_comandos(self):
        texto = self.ui.plainTextEdit.toPlainText()
        linhas = texto.splitlines()
        formatos_validos = [
            r"^B-?\d+$",
            r"^O-?\d+$",
            r"^C-?\d+$",
            r"^MP-?\d+$",
            r"^GP-?\d+$",
            r"^LT-?\d+$",
            r"^G-?\d+$",
            r"^FIM$",
            r"^Z$",
        ]

        self.setEnabled(False)

        for i, linha in enumerate(linhas, start=1):
            comando = linha.strip()
            if not comando:
                continue  # ignora linhas vazias
            if comando == "FIM":
                break

            # verifica se o comando bate com algum formato válido
            if not any(re.match(f, comando) for f in formatos_validos):
                QMessageBox.critical(self, "Erro de Comando", f"Erro na linha {i}: '{linha}' não é um comando válido.")
                self.setEnabled(True)
                return

            # envia comando
            if self.leitor and self.leitor.conectado:
                self.leitor.enviar_comando(comando)
            else:
                QMessageBox.warning(self, "Erro", "Arduino não conectado.")
                break
            while True:
                resposta = self.leitor.arduino.readline().decode(errors='ignore').strip()
                if resposta:
                    print("oi")
                    break
                #time.sleep(0.1)
        self.setEnabled(True)
        QMessageBox.information(self, "Concluído", "Todos os comandos foram executados.")
 
    def salvar(self):
        caminho_arquivo, _ = QFileDialog.getSaveFileName(self, "Salvar Arquivo", "", "Arquivos de Texto (*.txt)")
        if caminho_arquivo:
            try:
                texto = self.ui.plainTextEdit.toPlainText()
                with open(caminho_arquivo, 'w', encoding='utf-8') as arquivo:
                    arquivo.write(texto)
                QMessageBox.information(self, "Sucesso", "Arquivo salvo com sucesso!")
            except Exception as e:
                QMessageBox.critical(self, "Erro", f"Erro ao salvar o arquivo:\n{e}")

    def carregar(self):
        caminho_arquivo, _ = QFileDialog.getOpenFileName(self, "Abrir Arquivo", "", "Arquivos de Texto (*.txt)")
        if caminho_arquivo:
            try:
                with open(caminho_arquivo, 'r', encoding='utf-8') as arquivo:
                    conteudo = arquivo.read()
                    self.ui.plainTextEdit.setPlainText(conteudo)
                QMessageBox.information(self, "Sucesso", "Arquivo carregado com sucesso!")
            except Exception as e:
                QMessageBox.critical(self, "Erro", f"Erro ao carregar o arquivo:\n{e}")

    def closeEvent(self, event):
        try:
            if self.leitor and self.leitor.conectado:
                # Envia comando de reset para o Arduino
                self.leitor.enviar_comando("FIM")
            if self.leitor:
                self.leitor.parar()
        except Exception as e:
            print("Erro no closeEvent:", e)

        event.accept()

    def sobre(self):
        self.ui.stackedWidget.setCurrentIndex(5)

    def escolha(self):
        self.ui.stackedWidget.setCurrentIndex(1)
         #fecha o arquivo
        if self.modo_manual_ativo and self.arquivo_log:
                self.arquivo_log.close()
                self.arquivo_log = None
                self.modo_manual_ativo = False
                print("[LOG] Arquivo de log fechado.")

    def ajuda(self):
        self.ui.stackedWidget.setCurrentIndex(4)

    def paginicial(self):
        self.ui.stackedWidget.setCurrentIndex(0)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    janela = InterfaceTCC()
    janela.show()
    sys.exit(app.exec_())
