from python_files.classes import Window
from PyQt5.QtWidgets import QApplication
import sys


if __name__== "__main__":
    app = QApplication(sys.argv)
    win = Window()
    sys.exit(app.exec_())
