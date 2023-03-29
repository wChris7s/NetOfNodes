import pygame
import math

# Define some colors
COLOR_INICIO = (184, 179, 216, 1)
COLOR_FINAL = (255, 0, 0)
COLOR_NULL = (0, 0, 0)
COLOR_CAMINO = (64, 81, 114, 1)
COLOR_PISO = (40, 48, 63, 1)
COLOR_FONDO = (9, 10, 12, 1)

with open('data.txt') as data:
    temp = data.read().splitlines()
    net = []
    print("--------------------------")
    print(temp[0])  # DFS
    print(temp[1])  # INICIO
    print(temp[2])  # FIN
    print(temp[3])  # COLS
    print(temp[4])  # ROWS
    print("--------------------------")
    """
    for i in range(5, len(temp)):
        for j in range(len(temp[5])):
            print(temp[i][j] + " ", end="")
        print()
    """
    for i in range(5, len(temp)):
        net.append(temp[i])

    rows = len(net)
    cols = len(net[0])

    pygame.init()

    # Set the HEIGHT and WIDTH of the screen
    WINDOW_SIZE = [640, 640]

    # This sets the WIDTH and HEIGHT of each grid location
    WIDTH = (WINDOW_SIZE[0] / math.sqrt(rows * cols))
    HEIGHT = (WINDOW_SIZE[1] / math.sqrt(rows * cols))
    print(WIDTH, HEIGHT)

    screen = pygame.display.set_mode(WINDOW_SIZE)
    # Set title of screen
    pygame.display.set_caption(temp[0])
    # Loop until the user clicks the close button.
    done = False
    # Used to manage how fast the screen updates
    clock = pygame.time.Clock()

    # -------- Main Program Loop -----------
    while not done:
        for event in pygame.event.get():  # User did something
            if event.type == pygame.QUIT:  # If user clicked close
                done = True  # Flag that we are done so we exit this loop

        # Set the screen background
        screen.fill(COLOR_FONDO)

        # Draw the grid
        color = 0
        for row in range(rows):
            for column in range(cols):
                if net[row][column] == '0':
                    color = COLOR_PISO
                elif net[row][column] == ' ':
                    color = COLOR_NULL
                elif net[row][column] == '+':
                    color = COLOR_CAMINO
                elif net[row][column] == 'A':
                    color = COLOR_INICIO
                elif net[row][column] == 'B':
                    color = COLOR_FINAL
                rect = pygame.Rect(column * HEIGHT + 1, row * WIDTH + 1, WIDTH - 1, HEIGHT - 1)
                pygame.draw.rect(screen, color, rect)

        # Limit to 60 frames per second
        clock.tick(60)

        # Go ahead and update the screen with what we've drawn.
        pygame.display.flip()

    pygame.quit()
