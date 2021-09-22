from classes import Window
from PyQt5.QtWidgets import QApplication
import sys
"""
1) написать окно
2) курлить страницу и выводить текст в кавансы
3) написать классы виджетов
4) научиться позиционировать виджеты парсить там чего-то
5) добавить кнопки

"""

if __name__== "__main__":
    app = QApplication(sys.argv)
    win = Window()
    sys.exit(app.exec_())
