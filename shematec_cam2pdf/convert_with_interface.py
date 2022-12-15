import sys
from PyQt5.QtWidgets import (QWidget, QLabel, QLineEdit,
    QTextEdit, QGridLayout, QApplication)
from PyQt5.QtWidgets import QPushButton, QMessageBox

def fun(file_path_, folder_path_):
    poppler_path = r"Release-22.12.0-0\poppler-22.12.0\Library\bin"
    pdf_path = (file_path_) #r"C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\Privivka.pdf"
    saving_folder = (folder_path_)#r"C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\saved_bmp"
    print(pdf_path)
    print(saving_folder)
    # saving folder for bmp defenition

    import os
    dir_list = os.listdir(saving_folder)

    ### file name defining
    file_name = ""
    for i in range(len(pdf_path)-4, 0, -1):
        if pdf_path[i] == "\\":
            file_name = pdf_path[(i + 1): -4]
            break

    # just add current time
    import datetime
    e = datetime.datetime.now()
    file_name += "_" + "%s_%s_%s_%s_%s_%s" % (e.year, e.month, e.day, e.hour, e.minute, e.second)

    ## checker for the same names to avoid resaving of file (for dont lose the prev version of file)
    while True:
        flag = 0
        for i in dir_list:
            if i == file_name:
                flag = 1
                file_name += "(1)"
        if flag == 0:
            break

    # convertation part
    from pdf2image import convert_from_path
    pages = convert_from_path(pdf_path = pdf_path, poppler_path= poppler_path)


    c = 1
    for page in pages:
        img_name = file_name + f"{c}.bmp"
        page.save(os.path.join(saving_folder, img_name), "BMP")
        c += 1

    ## resize of pic
    from PIL import Image
    img_path = saving_folder
    image = Image.open(img_path + "\\" + img_name)
    image_size = image.size
    #coefficient of resize
    x_coef = 1
    y_coef = 2
    new_image = image.resize((image_size[0] * x_coef, image_size[1] * y_coef))
    new_image.save(img_path + "\\" + "resized" + "\\" + img_name)

    new_image.show()

class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        path_to_file = QLabel('pdf file absolute path')
        folder_for_saving = QLabel('save folder path')
        review = QLabel('Convert')

        self.path_file_Edit = QLineEdit()
        self.path_folder_Edit = QLineEdit()
        self.button_Edit = QPushButton('Start', self)

        self.button_Edit.setFixedSize(200,50)
        self.button_Edit.clicked.connect(self.main_method)
        grid = QGridLayout()
        grid.setSpacing(10)
        ##
        grid.addWidget(path_to_file, 1, 0)
        grid.addWidget(self.path_file_Edit, 1, 1)

        grid.addWidget(folder_for_saving, 2, 0)
        grid.addWidget(self.path_folder_Edit, 2, 1)

        grid.addWidget(review, 4, 0)
        grid.addWidget(self.button_Edit, 4, 1)

        self.setLayout(grid)

        self.setGeometry(300, 300, 1000, 500)
        self.setWindowTitle('Pdf conv')
        self.show()
    def main_method(self):
        file_path_ = self.path_file_Edit.text()
        folder_path_ = self.path_folder_Edit.text()

        if (file_path_ == "") or (folder_path_ == ""):
            QMessageBox.about(self, "ERORR", "U have empty field")

        try:
            fun(file_path_, folder_path_)
        except:
            QMessageBox.about(self, "ERORR", "Something went wrong \n check the folder path and file name")



if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
