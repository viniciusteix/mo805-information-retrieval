import numpy as np
import matplotlib.pylab as ply
import os
import glob

labels_images = []

def getImagesFromUrl(main_folder, folder, pasta):
    if os.path.isdir(main_folder + folder):  # if path is valid
        os.chdir(main_folder + folder)  # get in the folder
        for file in glob.glob("*"):  # for each file inside the folder
            if os.path.isdir(main_folder + folder + file):  # if the file is a folder
                labels_images[file] = []
                # recursively get in inside the folder
                getImagesFromUrl(main_folder, folder + file + '/', file)
            else:  # otherwise, the file is a handbag image
                if((file).endswith(".gif") or (file).endswith(".png") or (file).endswith(".jpeg") or (file).endswith(".jpg")):
                    labels_images.append(main_folder + folder + file)


def conversion(source_path, output_path,str_size):
    for img_path in labels_images:
        img = ply.imread(img_path)
        try:
            img = img[:,:,0]
        except:
            None;
        img = np.ceil(img/255)
        filename = source_path+output_path+img_path[str_size:-4]+'.pgm'
        fout=open(filename, 'wb')
        # define PGM Header
        pgmHeader = 'P2' + '\n' + str(img.shape[1]) + ' ' + str(img.shape[0]) + '\n' + str(1) +  '\n'
        pgmHeader_byte = bytearray(pgmHeader,'utf-8')
        fout.write(pgmHeader_byte)
        
        img_ = np.reshape(img,(img.shape[0],img.shape[1]))
        
        for j in range(img_.shape[0]):
            bnd = list(img_[j,:])
            bnd_str = np.char.mod('%d',bnd)
            bnd_str = np.append(bnd_str,'\n')
            bnd_str = [' '.join(bnd_str)][0]    
            bnd_byte = bytearray(bnd_str,'utf-8')
            fout.write(bnd_byte)
        fout.close()


def main():
    source_path = "/home/vinicius/Área de Trabalho/"
    path_images = "mpeg7/"
    output_path = "mpeg_new/"
    str_size = len(source_path+path_images)

    getImagesFromUrl(source_path, path_images, "")
    conversion(source_path,output_path,str_size)

if __name__ == '__main__':
    main()