from PIL import Image

def derivate_forward(fx, fx_forward, delta_x):
	return (fx_forward - fx)/delta_x


def derivate_backward(fx, fx_backward, delta_x):
	return (fx - fx_backward)/delta_x

def derivate_central(fx_forward, fx_backward, delta_x):
	return (fx_forward - fx_backward)/(2*delta_x)

img_open = Image.open('img_open.png') # Imagem a  qual  o objeto vai representar
img_open_mat = img_open.load()  # Carregando a imagem

img_exit = Image.new('L', img_open.size) # Imagem de saida
img_exit_mat = img_exit.load()  # Carregando a imagem

print(img_open.size) # Printando as dimenções da matriz da imagem
result = 0
for x in range(0, img_open.size[0]-1):
	for y in range(0, img_open.size[1]-1):
		if x == 1:
			result = derivate_forward(img_open_mat[x,y][0], img_open_mat[x+1, y][0], 1)
		elif x == img_open.size[0]:
			result = derivate_backward(img_open_mat[x,y][0], img_open_mat[x-1, y][0], 1)
		else:
			result = derivate_central(img_open_mat[x+1,y][0], img_open_mat[x-1, y][0], 1)

		if result < 127.5:
			img_exit_mat[x,y] = 255
		else:
			img_exit_mat[x,y] = 0

img_exit.save('img_exit.png')