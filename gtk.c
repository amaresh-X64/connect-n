#include <gtk/gtk.h>
#include <stdio.h>

#include <unistd.h>

// Global Variables
int global_rows;
int global_cols;
int players;
int currentPlayer;
int moves;
int winCondition;
char board[30][30];

GtkWidget *new_window;
GtkWidget *gridBoard;
GtkWidget *gridInput;

// typedef struct {
//     int rows;
//     int cols;
//     int players;
//     int currentPlayer;
//     int moves;
// } CallbackData;

// Connect functions:
void initializeBoard(int ROWS, int COLUMNS, char (*board)[COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            board[row][col] = ' ';
        }
    }
}
void printBoard(int ROWS, int COLUMNS, char (*board)[COLUMNS], GtkGrid *grid)
{
    char newLine[3];
    int row = 0;
    int col = 0;
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLUMNS; col++)
        {
            char board_op[7];
            snprintf(board_op, sizeof(board_op), "| %c ", board[row][col]);
            GtkWidget *boardOP = gtk_label_new(board_op);
            gtk_grid_attach(grid, boardOP, col, row, 1, 1);
        }
        snprintf(newLine, sizeof(newLine), " |");
        GtkWidget *newLineOP = gtk_label_new(newLine);
        gtk_grid_attach(grid, newLineOP, col, row, 1, 1);
    }

    // Column labels
    for (col = 0; col < COLUMNS; col++)
    {
        char col_no[5];
        if (col <= 10)
            snprintf(col_no, sizeof(col_no), "   %d", col + 1);
        if (col > 10)
            snprintf(col_no, sizeof(col_no), "  %d", col + 1);

        GtkWidget *colLabel = gtk_label_new(col_no);
        gtk_grid_attach(grid, colLabel, col, row, 1, 1);
    }

    // Attach an empty label at the end to fill the last cell
    // GtkWidget *emptyLabel = gtk_label_new("");
    // gtk_grid_attach(grid, emptyLabel, col, row+1, 1, 1);
}
int dropPiece(int col, char player, int ROWS, int COLUMNS, char (*board)[COLUMNS])
{
    for (int row = ROWS - 1; row >= 0; row--)
    {
        if (board[row][col] == ' ')
        {
            board[row][col] = player;
            return 1;
        }
    }
    return 0;
}
int checkWin(char player, int ROWS, int COLUMNS, char (*board)[COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col <= COLUMNS - 4; col++)
        {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
            {
                return 1;
            }
        }
    }

    for (int col = 0; col < COLUMNS; col++)
    {
        for (int row = 0; row <= ROWS - 4; row++)
        {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
            {
                return 1;
            }
        }
    }

    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 0; col <= COLUMNS - 4; col++)
        {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player)
            {
                return 1;
            }
        }
    }
    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 3; col < COLUMNS; col++)
        {
            if (board[row][col] == player &&
                board[row - 1][col - 1] == player &&
                board[row - 2][col - 2] == player &&
                board[row - 3][col - 3] == player)
            {
                return 1;
            }
        }
    }

    for (int row = 0; row < ROWS - 3; row++)
    {
        for (int col = 0; col < COLUMNS - 3; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
            {
                return 1;
            }
        }
    }

    for (int row = 0; row < ROWS - 3; row++)
    {
        for (int col = COLUMNS - 1; col >= 3; col--)
        {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player)
            {
                return 1;
            }
        }
    }

    return 0;
}
char fun(int currentplayer)
{
    switch (currentplayer)
    {
    case 1:
        return 'X';
    case 2:
        return 'O';
    case 3:
        return 'Y';
    case 4:
        return 'Z';
    case 5:
        return 'A';
    }
}
int fun1(int currentPlayer, int players)
{
    switch (players)
    {
    case 2:
    {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        return currentPlayer;
    }
    case 3:
    {
        switch (currentPlayer)
        {
        case 1:
            currentPlayer = 2;
            break;
        case 2:
            currentPlayer = 3;
            break;
        case 3:
            currentPlayer = 1;
            break;
        }
        return currentPlayer;
    }
    case 4:
    {
        switch (currentPlayer)
        {
        case 1:
            currentPlayer = 2;
            break;
        case 2:
            currentPlayer = 3;
            break;
        case 3:
            currentPlayer = 4;
            break;
        case 4:
            currentPlayer = 1;
            break;
        }
        return currentPlayer;
    }
    case 5:
    {
        switch (currentPlayer)
        {
        case 1:
            currentPlayer = 2;
            break;
        case 2:
            currentPlayer = 3;
            break;
        case 3:
            currentPlayer = 4;
            break;
        case 4:
            currentPlayer = 5;
            break;
        case 5:
            currentPlayer = 1;
            break;
        }
        return currentPlayer;
    }
    }
}

void clear_text(GtkTextView *text_view)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, "", -1);
}


void clearGrid(GtkGrid *grid) {
    GList *children, *iter;

    // Get the list of children in the grid
    children = gtk_container_get_children(GTK_CONTAINER(grid));

    // Iterate through the list and remove each child
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_container_remove(GTK_CONTAINER(grid), GTK_WIDGET(iter->data));
    }

    // Free the list
    g_list_free(children);
}


// void clearGrid(GtkGrid *grid)
// {
//     GList *children, *iter;

//     // Get the list of children in the grid
//     children = gtk_container_get_children(GTK_CONTAINER(grid));

//     // Iterate through the list and remove each child
//     for (iter = children; iter != NULL; iter = g_list_next(iter))
//     {
//         gtk_container_remove(GTK_CONTAINER(grid), GTK_WIDGET(iter->data));
//     }

//     // Free the list
//     g_list_free(children);
// }

void computeInput(GtkWidget *widget, gpointer data)
{
    GtkEntry *userEntry = GTK_ENTRY(data);
    const char *userInput = gtk_entry_get_text(userEntry);
    int colInput = atoi(userInput) - 1;

    if (colInput < 0 || colInput >= global_cols)
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Invalid column. Try again.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        winCondition = 1;
        return;
        // continue;
    }

    if (dropPiece(colInput, fun(currentPlayer), global_rows, global_cols, board))   //piece is successfully dropped
    {
        if (checkWin(fun(currentPlayer), global_rows, global_cols, board))
        {
            // clearGrid(GTK_GRID(gridBoard));
            printBoard(global_rows, global_cols, board, GTK_GRID(gridBoard));
            char *winMessage = g_strdup_printf("Player %d wins!", currentPlayer);
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "%s", winMessage);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            winCondition = 2;
            return;
            // break;
        }
        moves++;
        if (moves == global_rows * global_cols)
        {
            // clearGrid(GTK_GRID(gridBoard));
            printBoard(global_rows, global_cols, board, GTK_GRID(gridBoard));
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "It's a draw!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            winCondition = 2;
            return;
            // break;
        }
        currentPlayer = fun1(currentPlayer, players);
        winCondition = 0;
        recursion(currentPlayer);
    }
    else
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Column is full, try again.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        winCondition = 1;
        return;
        // continue;
    }

    gtk_widget_show_all(new_window);
}

void recursion(int CPlayer)
{
    clearGrid(GTK_GRID(gridBoard));
    printBoard(global_rows, global_cols, board, GTK_GRID(gridBoard));
    if (winCondition == 0) // normal condition
    {
        // while (gtk_events_pending())
        // {
        //     gtk_main_iteration();
        // }
        
        // sleep(2);
        char userInput[30];
        clearGrid(GTK_GRID(gridInput));
        snprintf(userInput, sizeof(userInput), "Player %d, enter a column: ", currentPlayer);
        GtkWidget *userIP = gtk_label_new(userInput);
        gtk_grid_attach(GTK_GRID(gridInput), userIP, 0, global_rows, 1, 1);
        GtkWidget *userEntry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(gridInput), userEntry, 1, global_rows, 1, 1);
        GtkWidget *buttonIP = gtk_button_new_with_label("OK");
        gtk_grid_attach(GTK_GRID(gridInput), buttonIP, 2, global_rows, 1, 1);
        g_object_set_data(G_OBJECT(buttonIP), "userEntry", userEntry);

        g_signal_connect(buttonIP, "clicked", G_CALLBACK(computeInput), userEntry);
        gtk_widget_show_all(new_window);
    }
    else if (winCondition == 1) // invalid case, player has to play again
    {
        recursion(CPlayer);
    }
    else // game has been won
    {
        clearGrid(GTK_GRID(gridBoard));
        printBoard(global_rows, global_cols, board, GTK_GRID(gridBoard));
        exit(0);
    }
}

void newWindow(int rows, int cols, int playersNos)
{
    global_rows = rows;
    global_cols = cols;
    players = playersNos;

    new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), "Connect!");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 200, 100);

    // grid of grids
    GtkWidget *main_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(new_window), main_grid);
    // gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    // gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    // char board[rows][cols];
    initializeBoard(global_rows, global_cols, board);
    currentPlayer = 1;
    moves = 0;
    winCondition = 0;

    GtkWidget *gridTop = gtk_grid_new();
    GtkWidget *label_cBoard = gtk_label_new("Current board:");
    gtk_grid_attach(GTK_GRID(gridTop), label_cBoard, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), gridTop, 0, 0, 1, 1);

    gridBoard = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(main_grid), gridBoard, 0, 1, 1, 1);

    gridInput = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(main_grid), gridInput, 0, 2, 1, 1);

    // while (winCondition == 0)
    //{
    // clearGrid(GTK_GRID(gridBoard));
    //  printBoard(rows, cols, board, GTK_GRID(gridBoard));

    // clearGrid(GTK_GRID(gridInput));
    //  char userInput[30];
    //  snprintf(userInput, sizeof(userInput), "Player %d, enter a column: ", currentPlayer);
    //  GtkWidget *userIP = gtk_label_new(userInput);
    //  gtk_grid_attach(GTK_GRID(gridInput), userIP, 0, rows, 1, 1);
    //  GtkWidget *userEntry = gtk_entry_new();
    //  gtk_grid_attach(GTK_GRID(gridInput), userEntry, 1, rows, 1, 1);
    //  GtkWidget *buttonIP = gtk_button_new_with_label("OK");
    //  gtk_grid_attach(GTK_GRID(gridInput), buttonIP, 2, rows, 1, 1);
    //  g_object_set_data(G_OBJECT(buttonIP), "userEntry", userEntry);

    // g_signal_connect(buttonIP, "clicked", G_CALLBACK(computeInput), userEntry);
    // g_object_set_data(G_OBJECT(buttonIP), "callback_data", params);

    // gtk_widget_show_all(new_window);
    //}

    recursion(currentPlayer);
    gtk_widget_show_all(new_window);
}

void on_button_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry1 = GTK_ENTRY(data);
    const char *text1 = gtk_entry_get_text(entry1);
    int num1 = atoi(text1);

    GtkEntry *entry2 = GTK_ENTRY(g_object_get_data(G_OBJECT(widget), "entry2"));
    const char *text2 = gtk_entry_get_text(entry2);
    int num2 = atoi(text2);

    GtkEntry *entry3 = GTK_ENTRY(g_object_get_data(G_OBJECT(widget), "entry3"));
    const char *text3 = gtk_entry_get_text(entry3);
    int num3 = atoi(text3);

    if (num1 < 6 || num2 < 6 || num3 < 2 || num3 > 6)
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Bad values.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    newWindow(num1, num2, num3);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Connect!");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 200);

    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();
    GtkWidget *entry3 = gtk_entry_new();
    GtkWidget *important = gtk_label_new("Important information:\nRow and column values must be above '6'.\nNumber of players 'x' must adhere to (1<x<6).");
    GtkWidget *label1 = gtk_label_new("Enter the number of rows:");
    GtkWidget *label2 = gtk_label_new("Enter the number of columns:");
    GtkWidget *label3 = gtk_label_new("Enter the number of players:");
    GtkWidget *button = gtk_button_new_with_label("Play!");

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    gtk_grid_attach(GTK_GRID(grid), important, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry3, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), text_view, 0, 5, 1, 1);

    g_object_set_data(G_OBJECT(button), "entry2", entry2);
    g_object_set_data(G_OBJECT(button), "entry3", entry3);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry1);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}