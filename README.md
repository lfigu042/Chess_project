# Chess_project
Program that stores a chessboard in a 2D array of integers.
By Laura Figueroa 4918449

The game begins asking user for commands
    1-> 'quit' ends the game
    2-> 'mv xx yy' will move a piece from 'xx' to 'yy'
        a-> 'isLegalMove' method checks legality of moves for each different piece:
            i-> ROOKS can only move up/down or left/right while path is clear.
           ii-> PAWNS can move 1 or 2 spaces if never moved before, else only 1 move horizontally and towards the enemy side while path is clear.
          iii-> KNIGHTS move in 'L' shape and can 'jump' enemies.
           iv-> BISHOPS move diagonally while path is clear.
            v-> QUEEN can move like a bishop or a rook while path is clear.
           vi-> KING can only move one space around him. 
        b-> 'mv' command also has check for the right color to play to respect BLACK vs WHITE turns
    3-> 'cp xx yy' means 'xx' wants to capture 'yy'
        a-> 'isLegalCapture' checks if the capture is legal.
            i-> method will check that two pieces are opposite colors.
           ii-> method will check that there exist a piece in the source and target location.
          iii-> PAWNS are special case and will capture one space away and vertically.
           iv-> Other pieces will check 'isLegalMove' and then allow the capture.
    4-> 'show' prints the current state of the board 