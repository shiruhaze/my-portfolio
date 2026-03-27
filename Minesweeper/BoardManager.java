import java.util.Random;
import java.util.Stack;

public class BoardManager {
    protected static Cell[][] board;
    protected static final int SIZE = 6;
    protected static final int MINES = 8;
    private int revealedCells = 0;
    private Stack<int[]> moveHistory = new Stack<>();  
    
    static Random rand = new Random();
    static int zeroRow = rand.nextInt(SIZE);
    static int zeroCol = rand.nextInt(SIZE);

    public BoardManager() { 
        board = new Cell[SIZE][SIZE]; 
        initBoard();
        placeMines();
    }

    private void initBoard() { 
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                board[row][col] = new Cell(); 
            }
        }
    }

    private void placeMines() {
        int minesPlaced = 0;
        while (minesPlaced < MINES) {
            int row = rand.nextInt(SIZE); 
            int col = rand.nextInt(SIZE); 
            if (!board[row][col].isMine()) { 
                board[row][col].setMine(true);  
                minesPlaced++;
            }
        }
    }

    public boolean reveal(int row, int col){ 
        if (board[row][col].isRevealed()) {
            System.out.println("Already revealed!\n");
            return true; 
        }

        moveHistory.push(new int[]{row, col});
        board[row][col].setRevealed(true); 

        if (board[zeroRow][zeroCol].isRevealed()) { 
            revealAroundZero();
        }

        if (board[row][col].isMine()) {
            return false; 
        } else {
            revealedCells++;
            return true; 
        }
    }

    public boolean isCellRevealed(int row, int col){
        return board[row][col].isRevealed();
    }

    public boolean undoLastMove() {
        if (moveHistory.isEmpty()) {
            System.out.println("No moves to undo!");
            return false;
        }

        int[] lastMove = moveHistory.pop();
        int row = lastMove[0];
        int col = lastMove[1];

        board[row][col].setRevealed(false);
        revealedCells--;
        return true;
    }

    public boolean isWin() {
        return revealedCells == (SIZE * SIZE - MINES);  
    }

    public void flags(int rowIndex, int colIndex) {
        int count = 0; 
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                if (row == 0 && col == 0) {
                    continue;
                }
                int checkRow = rowIndex + row;
                int checkCol = colIndex + col;

                if (checkRow >= 0 && checkRow < SIZE && checkCol >= 0 && checkCol < SIZE && board[checkRow][checkCol].isMine()) {
                    count++;
                }
            }
        }

        if (count == 0) {
            System.out.print("[-]");
        } else {
            System.out.print("[" + count + "]");
        }
    }

    public static void revealAroundZero() { 
        for (int rows = -1; rows <= 1; rows++) {
            for (int cols = -1; cols <= 1; cols++) {
                if (rows == 0 && cols == 0) {
                    continue;
                }

                int checkRows = zeroRow + rows;
                int checkCols = zeroCol + cols;

                if (checkRows >= 0 && checkRows < SIZE && checkCols >= 0 && checkCols < SIZE) { 
                    board[checkRows][checkCols].setRevealed(true);
                }
            }
        }
    }

    public void displayBoard() {
        System.out.print("   ");
        for (int col = 1; col <= SIZE; col++) {
            System.out.print(col + "  ");
        }
        System.out.println();

        for (int row = 0; row < SIZE; row++) {
            System.out.print((row + 1) + " ");
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col].isRevealed()) {
                    if (board[row][col].isMine()) {
                        System.out.print("[*]");
                    } else if (row == zeroRow && col == zeroCol) {
                        System.out.print("[0]");
                    } else {
                        flags(row, col);
                    }
                } else {
                    System.out.print("[ ]");
                }
            }
            System.out.println();
        }
    }
}


