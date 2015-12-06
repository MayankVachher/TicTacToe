import sys, pygame, time

def ind_to_pos(ind):
	x = ind/3
	y = ind%3
	return (x,y)

def print_board(board):
	for x in board:
		for y in x:
			if y == 0: print "0",
			if y == 1: print "1",
			if y == -1: print "-1",
		print ""

def check_win(board):
	for i in range(3):
		if(board[i][0] and board[i][1] == board[i][2] and board[i][2] == board[i][0]): return board[i][0]
		if(board[0][i] and board[1][i] == board[2][i] and board[2][i] == board[0][i]): return board[0][i]
	if(board[1][1] == 0): return 0
	if(board[1][1] == board[0][0] and board[2][2] == board[1][1]): return board[1][1]
	if(board[1][1] == board[0][2] and board[1][1] == board[2][0]): return board[1][1]
	return 0

def board_full(board):
	for x in board:
		for y in x:
			if y == 0: return False
	return True

def computer_move(board):
	pos = 0
	best_i = 1
	best_j = 1
	points = float("inf")
	move_points = 0
	for x in range(len(board)):
		for y in range(len(board)):
			if board[x][y] == 0:
				board[x][y] = -1
				move_points = minimax(board,1)
				if(points  > move_points):
					points = move_points
					pos = x*3 + y
					best_i = x
					best_j = y

				board[x][y] = 0
	return pos

def minimax(board, player):
	val = check_win(board)
	points = float("inf")
	move_points = 0
	if player == 1: points = -points

	if val != 0 or board_full(board): return val

	for x in range(len(board)):
		for y in range(len(board)):
			if board[x][y] == 0:
				if player == -1:
					board[x][y] = -1
					move_points = minimax(board,1)
					if(points > move_points): points = move_points
				else:
					board[x][y] = 1
					move_points = minimax(board,-1)
					if(points < move_points): points = move_points
				board[x][y] = 0
	return points

def run_game():

	board = [[0,0,0],[0,0,0],[0,0,0]]

	#------------------------------------------
	#Pygame starts

	pygame.init()
	size = width, height = 480, 480

	#------------------------------------------
	#Screen Setup

	FONT = pygame.font.SysFont('Arial', 150)
	FONT2 = pygame.font.SysFont('Arial', 50)
	FONT3 = pygame.font.SysFont('Arial', 23)
	WINDOW = pygame.display.set_mode(size)
	CAPTION = pygame.display.set_caption('Tic-Tac-Toe')
	SCREEN = pygame.display.get_surface()
	SCREEN.fill((150, 141, 131))
	TRANSPARENT = pygame.Surface(size)
	TRANSPARENT.set_alpha(255)
	TRANSPARENT.fill((255,255,255))
	GAMEEND = pygame.Surface(size)
	GAMEEND.set_alpha(90*255/100)
	GAMEEND.fill((255, 255, 255))

	#------------------------------------------
	#Rectangle Setup

	rect1 = pygame.draw.rect(SCREEN, (238,228,218), (0,0,155,155))
	rect2 = pygame.draw.rect(SCREEN, (238,228,218), (165,0,155,155))
	rect3 = pygame.draw.rect(SCREEN, (238,228,218), (330,0,160,155))
	rect4 = pygame.draw.rect(SCREEN, (238,228,218), (0,165,155,155))
	rect5 = pygame.draw.rect(SCREEN, (238,228,218), (165,165,155,155))
	rect6 = pygame.draw.rect(SCREEN, (238,228,218), (330,165,160,155))
	rect7 = pygame.draw.rect(SCREEN, (238,228,218), (0,330,155,160))
	rect8 = pygame.draw.rect(SCREEN, (238,228,218), (165,330,155,160))
	rect9 = pygame.draw.rect(SCREEN, (238,228,218), (330,330,160,160))

	#-----------------------------------------
	#X and O Setup

	text_X = FONT.render("X", 1, (246, 36, 89))
	text_O = FONT.render("O", 1, (68, 108, 179))
	turn_decision = 1
	placed_text = []

	#-----------------------------------------
	#Refresh Display

	pygame.display.flip()

	#-----------------------------------------
	#Main Loop

	print_board(board)

	rectangles = [rect1,rect2,rect3,rect4,rect5,rect6,rect7,rect8,rect9]
	while check_win(board) == 0 and len(placed_text) != 9:
		if(turn_decision==1):
			pos = computer_move(board)
			textpos = text_X.get_rect()
			textpos.center = rectangles[pos].center
			placed_text.append(textpos)
			SCREEN.blit(text_X,textpos)
			pos = ind_to_pos(pos)
			board[pos[0]][pos[1]] = -1
			turn_decision = 0
			print_board(board)
			time.sleep(1)
			pygame.display.flip()

		pos = pygame.mouse.get_pos()
		mouse = pygame.draw.circle(TRANSPARENT, (0,0,0), pos, 0)
		
		#------------------------------------
		#Detect Events

		for event in pygame.event.get():
			if event.type == pygame.QUIT: sys.exit()
			elif event.type == pygame.MOUSEBUTTONDOWN:
				for rect in rectangles:
					if rect.contains(mouse) and rect.collidelist(placed_text) == -1:
						pos = ind_to_pos(rectangles.index(rect))
						print rect
						if turn_decision == 0:
							textpos = text_O.get_rect()
							textpos.center = rect.center
							placed_text.append(textpos)
							SCREEN.blit(text_O,textpos)
							board[pos[0]][pos[1]] = 1
							turn_decision = 1
						pygame.display.flip()
						print_board(board)

	if(check_win(board) == 0):
		print "Tie!"
		text_win = FONT2.render("TIE!", 1, (20,20,20))
	elif(check_win(board) == 1):
		print "Player 2 Wins!"
		text_win = FONT2.render("Player 2 (O) wins!", 1, (68, 108, 179))
	else:
		print "Player 1 Wins!"
		text_win = FONT2.render("Player 1 (X) wins!", 1, (246, 36, 89))

	textpos = text_win.get_rect()
	textpos.center = GAMEEND.get_rect().center
	textpos[1] = textpos[1] - 100
	GAMEEND.blit(text_win,textpos)
	
	playAgain = pygame.Surface((150,50))
	quitNow = pygame.Surface((150,50))
	playAgain.fill((39, 174, 96))
	quitNow.fill((211, 84, 0))

	text_play = FONT3.render("PLAY AGAIN", 1, (255, 255, 255))
	textpos = text_play.get_rect()
	textpos.center = playAgain.get_rect().center
	playAgain.blit(text_play,textpos)
	text_quit = FONT3.render("QUIT", 1, (255, 255, 255))
	textpos = text_quit.get_rect()
	textpos.center = quitNow.get_rect().center
	quitNow.blit(text_quit,textpos)

	SCREEN.blit(GAMEEND,(0,0))
	SCREEN.blit(playAgain,(45,300))
	SCREEN.blit(quitNow,(285,300))

	pygame.display.flip()

	playRect = pygame.draw.rect(TRANSPARENT,(255,0,0),(45,300,150,50))
	quitRect = pygame.draw.rect(TRANSPARENT,(255,0,0),(285,300,150,50))

	while True:
		
		pos = pygame.mouse.get_pos()
		mouse = pygame.draw.circle(TRANSPARENT, (0,0,0), pos, 0)

		for event in pygame.event.get():
			if event.type == pygame.QUIT: sys.exit()
			elif event.type == pygame.MOUSEBUTTONDOWN:
				if(playRect.contains(mouse)): return 1
				if(quitRect.contains(mouse)): sys.exit()

def main():
	while run_game() == 1:
		pass

if __name__ == '__main__':
	main()
