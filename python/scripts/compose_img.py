from PIL import Image
import os

for filename in os.listdir('./img'):
    if not filename.endswith('.png'):
        continue
    img = Image.open(os.path.join(f'./img/{filename}'))

    width, height = img.size
    print(width, height)
    rt = width * height // 10000
    img.thumbnail((width // 3.4, height // 3.4))

    img.save(f'./target/{filename}')
