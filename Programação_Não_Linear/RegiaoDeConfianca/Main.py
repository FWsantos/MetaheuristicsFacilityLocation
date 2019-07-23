from consolemenu import *
from consolemenu.format import *
from consolemenu.items import *
import numpy as np
import matplotlib.pyplot as plt #biblioteca de gráficos
from MetodosOI import *

def main_plot(f_x, b):
    x = np.arange(-1*b, b, 0.001)
    y = map(lambda u: f_x(f_x.dimensa0*[u]), x)
    plt.plot(x, list(y))

def ler_x(d):
	x = []
	print("Insira os valores de x")
	for i in range(d):
		text = 'x['+str(i)+'] = '
		a = float(input(text))
		x.append(a)
	return x
def buscas_exata_controller():
	print("Usar Secao Aurea")
	input()
def buscas_inexata_controller():
	print("Usar Armijo")
	input()
def cauchy_controller():
	print("Usar O metodo da regiao de confianca")
	input()
def op_funcao(entrada):
	input()
	input(entrada)
	# MetodosOI()
	# if(entrada[1] == '1'):

	# 	if(entrada[0] == 'G'):
	# 		x = ler_x(2)
def f1_ctrl(metodo):
	x= ler_x(2)
	if metodo == 'G':
		print(x)
		# b= float(input("Digite a amplitude: "))
		res = gradient_descent(x, F1(2))
		print('ponto encontrado = ', res[0])
		print('valor nesse ponto = ', res[1])
		# print(res)
		# print(res[len(res)])
		# resg = np.array(res)
		# plt.plot(resg[:,0], resg[:, 1], '+')
		# main_plot(F1(2), b)
		# plt.show()
		input()


def f2_ctrl(metodo):
	x= ler_x(2)
	if metodo == 'G':
		res = gradient_descent(x, F2(2))
		print('ponto encontrado = ', res[0])
		print('valor nesse ponto = ', res[1])
		input()

def f3_ctrl(metodo):
	x= ler_x(2)
	if metodo == 'G':
		res = gradient_descent(x, F3(2))
		print('ponto encontrado = ', res[0])
		print('valor nesse ponto = ', res[1])
		input()

def f4_ctrl(metodo):
	x= ler_x(2)
	if metodo == 'G':
		res = gradient_descent(x, F4(2))
		print('ponto encontrado = ', res[0])
		print('valor nesse ponto = ', res[1])
		input()

def f5_ctrl(metodo):
	x= ler_x(2)
	if metodo == 'G':
		res = gradient_descent(x, F5(2))
		print('ponto encontrado = ', res[0])
		print('valor nesse ponto = ', res[1])
		input()

def funcoes_controller(metodo):
	submenu_funcoes = SelectionMenu([], title=titulo, formatter=menu_format, prologue_text="Escolha a funcao para teste")
	submenu_funcoes.append_item(FunctionItem("pow(x[0],2) + 4*pow(x[1],2) - 4*x[0] - 8*x[1]", f1_ctrl, metodo))
	submenu_funcoes.append_item(FunctionItem("(x[0] - pow(x[1],2))*(x[0] - (0.5*pow(x[1],2)))", f2_ctrl, metodo))
	submenu_funcoes.append_item(FunctionItem("2*pow(x[0],3) - 3*pow(x[0],2) - 6*x[0]*x[1]*(x[0] - x[1] - 1)", f3_ctrl, metodo))
	submenu_funcoes.append_item(FunctionItem("0.5*sin(x[0])*sin(x[1]) + 0.5*exp(pow(x[0], 2)+pow(x[1], 2))", f4_ctrl, metodo))
	submenu_funcoes.append_item(FunctionItem("100*pow(x[1] - pow(x[0], 2), 2) + pow(1 - x[0], 2)", f5_ctrl, metodo))
	
	submenu_funcoes.show()
	# print("Usar a funcao ", a)
	# input()

menu_format = MenuFormatBuilder().set_border_style_type(MenuBorderStyleType.HEAVY_BORDER) \
        .set_title_align('center') \
        .set_subtitle_align('center') \
        .show_header_bottom_border(True)
        # .set_left_margin(6) \
        # .set_right_margin(6) \
# Create the menu
titulo = "Projeto Computacional I"
menu = ConsoleMenu(titulo, "Metodos de Otimização Irrestrita",formatter=menu_format)

submenu_funcoes = SelectionMenu([], title=titulo, formatter=menu_format, prologue_text="Escolha a funcao para teste")
# submenu_funcoes.append_item()
submenu_funcoes.append_item(FunctionItem("pow(x[0],2) + 4*pow(x[1],2) - 4*x[0] - 8*x[1]", funcoes_controller, 1))


submenu_gradiente = SelectionMenu([], title=titulo, formatter=menu_format, prologue_text="Escolha a busca unidimensional")
submenu_gradiente.append_item(FunctionItem("Busca Exata (Seção Aurea)", buscas_exata_controller))
submenu_gradiente.append_item(FunctionItem("Busca Inexata (Armijo)", buscas_inexata_controller))
# submenu_gradiente.append_item(FunctionItem("Foi", input, ["digite"]))
item_gradiente = FunctionItem("Gradiente", funcoes_controller, 'G')
# item_gradiente.set_menu(menu  )

# submenu_rg = SelectionMenu(["Passo de Cauchy"])
submenu_rg = SelectionMenu([], title=titulo, formatter=menu_format)
submenu_rg.append_item(FunctionItem("Passo de Cauchy", cauchy_controller))

item_rg = SubmenuItem("Regiao de confianca", submenu_rg, menu)

menu.append_item(item_gradiente)

menu.append_item(item_rg)

# Finally, we call show to show the menu and allow the user to interact
menu.show()