from PIL import Image

# Metodo da derivada utilizando a filosofia Forward
def derivate_forward(fx, fx_forward, delta_x):
	return (fx_forward - fx)/delta_x

# Metodo da derivada utilizando a filosofia Backward
def derivate_backward(fx, fx_backward, delta_x):
	return (fx - fx_backward)/delta_x

# Metodo da derivada utilizando a filosofia Central
def derivate_central(fx_forward, fx_backward, delta_x):
	return (fx_forward - fx_backward)/(2*delta_x)

img_open = Image.open('img_open.jpeg') # Imagem a  qual  o objeto vai representar
img_open_mat = img_open.load()  # Carregando a imagem para array

# Criando a imagem de saida
# new -> cria nova imagem
# '1' -> 1 bit pixel, ou é branco(1) ou preto(0)
# img_open.size -> imagem é criada com as dimensões de img_open
img_exit = Image.new('1' , img_open.size) 
img_exit_mat = img_exit.load()  # Carregando a imagem array

result = 0
# iterando cada pixel de img_open
for x in range(0, img_open.size[0]-1):
	for y in range(0, img_open.size[1]-1):
		if x == 0: # se estiver no limite esquerdo aplica forward
			result = derivate_forward(img_open_mat[x,y][0], img_open_mat[x+1, y][0], 1)
		elif x == img_open.size[0]-1: # se estiver no limite direito aplica backward
			result = derivate_backward(img_open_mat[x,y][0], img_open_mat[x-1, y][0], 1)
		else: # pixels em que se aplica a filosofia central
			result = derivate_central(img_open_mat[x+1,y][0], img_open_mat[x-1, y][0], 1)

		# falta comentar
		if result < 1:
			img_exit_mat[x,y] = 1
		else:
			img_exit_mat[x,y] = 0

# Salva a imagem saida
img_exit.save('img_exit.png')
