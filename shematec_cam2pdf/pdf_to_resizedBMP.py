
#paths of lib and pdf file
poppler_path = r"C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\Release-22.12.0-0\poppler-22.12.0\Library\bin"
pdf_path = r"C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\Privivka.pdf"

# saving folder for bmp defenition
import os
saving_folder = r"C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\saved_bmp"
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
img_path = r'C:\Users\Bogdan\PycharmProjects\PDF_2_BMP\saved_bmp'
image = Image.open(img_path + "\\" + img_name)
image_size = image.size
#coefficient of resize
x_coef = 1
y_coef = 2
new_image = image.resize((image_size[0] * x_coef, image_size[1] * y_coef))
new_image.save(img_path + "\\" + "resized" + "\\" + img_name)
