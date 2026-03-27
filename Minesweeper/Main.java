import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        BoardManager game = new BoardManager();
        Scanner scanner = new Scanner(System.in);
        Queue<Integer> turns = new LinkedList<>();
        LinkedList<Integer> undoList = new LinkedList<Integer>();
        playerTurn(scanner, turns, game, undoList);
        scanner.close();
    }
    
    public static void playerTurn(Scanner scanner, Queue<Integer> turns, BoardManager game, LinkedList<Integer> undoList) {
        int numOfPlayers = 0;
        boolean validInput = false;
        do {
            System.out.println("===============================");
            System.out.println("|    WELCOME TO MINESWEEPER!  |");
            System.out.println("===============================\n");
            System.out.print("Enter number of players (2-5): ");
            String input = scanner.nextLine();
            try {
                numOfPlayers = Integer.parseInt(input);
                if (numOfPlayers >= 2 && numOfPlayers <= 5) {
                    validInput = true;
                } else {
                    System.out.println("Invalid. Please enter between 2 and 5.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. ONLY enter a NUMBER between 2 and 5.");
            }
        } while (!validInput);
        
        for (int i = 1; i <= numOfPlayers; i++) {
            turns.offer(i);
        }
        board(game, scanner, turns, numOfPlayers, undoList);
    }
    
    public static void board(BoardManager game, Scanner scanner, Queue<Integer> turns, int numOfPlayers, LinkedList<Integer> undoList) {
        while (true) {
            if (turns.isEmpty()) {
                break;
            }
            int currentPlayer = turns.poll();
            boolean lost = false;
            boolean turnCompleted = false;
            
            while (!turnCompleted) {
                System.out.println("\nCurrent board:\n");
                game.displayBoard();
                System.out.println("[PLAYER " + currentPlayer + "'s turn]\n");
                int row = 0, col = 0;
               
                while (true) {
                    System.out.print("Enter row (1-6): ");
                    String rowInput = scanner.next();
                    try {
                        row = Integer.parseInt(rowInput);
                        if (row < 1 || row > 6) {
                            System.out.println("\nPlease enter a number between 1 and 6.");
                            continue;
                        }
                        break;
                    } catch (NumberFormatException e) {
                        System.out.println("\nInvalid input. ONLY enter a NUMBER between 1 and 6.");
                    }
                }
               
                while (true) {
                    System.out.print("Enter column (1-6): ");
                    String colInput = scanner.next();
                    try {
                        col = Integer.parseInt(colInput);
                        if (col < 1 || col > 6) {
                            System.out.println("\nPlease enter a number between 1 and 6.");
                            continue;
                        }
                        if (game.isCellRevealed(row - 1, col - 1)){
                            System.out.println("\nAlready revealed! Choose another cell.");
                            while (true) {
                                System.out.print("Enter row (1-6): ");
                                String rowInput = scanner.next();
                            try {
                                row = Integer.parseInt(rowInput);
                                 if (row < 1 || row > 6) {
                                System.out.println("Please enter a number between 1 and 6.");
                                continue;
                                }
                                break;
                            } catch (NumberFormatException e) {
                                System.out.println("Invalid input. ONLY enter a NUMBER between 1 and 6.");
                            }
                         }
                    continue;
                     }
                     break;
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid input. ONLY enter a NUMBER between 1 and 6.");
                    }
                }
                
                boolean safe = game.reveal(row - 1, col - 1);

                if (!safe) {
                    System.out.println("PLAYER " + currentPlayer + " stepped on a mine. Game Over! :p");
                    game.displayBoard();
                    lost = true;
                    numOfPlayers--;
                    turnCompleted = true;
                    break;
                }
                System.out.println("\nUpdated board after PLAYER " + currentPlayer + "'s move:\n");
                game.displayBoard();
                if (game.isWin()) {
                    System.out.println("Congratulations! PLAYER " + currentPlayer + " wins!");
                    game.displayBoard();
                    return;
                }
               
                boolean didUndo = false;
                
                if (!undoList.contains(currentPlayer)) {
                    while (true) {
                        System.out.print("Do you want to undo your last move? (Y/N): ");
                        String undoInput = scanner.next();
                        if (undoInput.equalsIgnoreCase("Y")) {
                            if (game.undoLastMove()) {
                                System.out.println("Last move undone.");
                                undoList.add(currentPlayer);
                                didUndo = true;
                            } else {
                                System.out.println("You cannot undo your move.");
                            }
                            break;
                        } else if (undoInput.equalsIgnoreCase("N")) {
                            break;
                        } else {
                            System.out.println("Invalid input. Please enter 'Y' or 'N'.");
                        }
                    }
                } else {
                    System.out.println("Undo not available for PLAYER " + currentPlayer + " (Only one undo per game).");
                }
                if (didUndo) {
                    continue;
                } else {
                    turnCompleted = true;
                }
            }
            if (!lost && numOfPlayers > 0) {
                turns.offer(currentPlayer);
            }
            if (numOfPlayers <= 0) {
                System.out.println("GAME OVER >>>>");
                break;
            }
        }
    }
} 
    

