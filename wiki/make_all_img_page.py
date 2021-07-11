import os
import glob

img_list = glob.glob("img/**/*svg", recursive=True)
img_list = [img for img in img_list if not "waveforms" in img]
img_list = [img.replace(', ', '%2C%20') for img in img_list]

with open('wiki/md/all_img_page.md', mode='w') as f:
    for img in img_list:
        f.write('### ' + img + '\n')
        f.write('![{0}]\n'.format(img))
        f.write('(https://github.com/hmdyt/b4ex_semiconductor/blob/main/{0})\n'.format(img))
print(img_list)