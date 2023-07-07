# (89110, Spring 2023, Assignment #7, Nadav Rutman Moshe, 325387082, rutmann)


def menu():
    """
    Print menu.

    The function prints the menu and asks for an option.

    Returns:
        string: the choice made by the user.
    """
    print('Choose an option:')
    print('0. Exit')
    print('1. Update settings')
    print('2. Play')
    print('3. View settings')
    print('4. Scoreboard')
    return input()


def print_invalid_settings():
    """Print invalid settings."""
    print('Invalid settings')


minimum_setting = 1
minimum_length = 2
key_index = 0
value_index = 1


def task1(settings):
    """
    Update settings.

    Args:
        settings (map): the settings

    The function updates the settings by the string it gets from the user and checks if
    the string is valid and if the settings are valid for the game.
    """
    settings_string = input('Enter settings:\n')
    # checks for the end and the first character
    if len(settings_string) < minimum_length or settings_string[0] != '{' or settings_string[-1] != '}':
        print_invalid_settings()
        return
    # takes off the first and last characters {}
    settings_string = settings_string[1:-1]
    # splits to different settings
    settings_string = settings_string.split(', ')
    temp_settings = {}
    for current_setting_string in settings_string:
        # splits the key from the value
        key_value = current_setting_string.split(':')
        if len(key_value) != minimum_length:
            print_invalid_settings()
            return
        key_value[key_index] = key_value[key_index].strip()
        key_value[value_index] = key_value[value_index].strip()
        # checks for spaces and double keys
        if ' ' in key_value[key_index] or ' ' in key_value[value_index] or key_value[key_index] in temp_settings.keys():
            print_invalid_settings()
            return
        temp_settings[key_value[key_index]] = key_value[value_index]

    if 'tries' in temp_settings.keys():
        # checks if the setting in tries is a number
        if temp_settings['tries'].isdigit():
            number_tries = int(temp_settings['tries'])
            if number_tries < minimum_setting:
                print_invalid_settings()
                return
        else:
            print_invalid_settings()
            return

    # checks if the setting in word_length is a number
    if 'word_length' in temp_settings.keys():
        if temp_settings['word_length'].isdigit():
            number_tries = int(temp_settings['word_length'])
            if number_tries < minimum_setting:
                print_invalid_settings()
                return
        else:
            print_invalid_settings()
            return
    # updates the new settings
    for adding_setting_string in settings_string:
        key_value = adding_setting_string.split(':')
        key_value[key_index] = key_value[key_index].strip()
        key_value[value_index] = key_value[value_index].strip()
        settings[key_value[key_index]] = key_value[value_index]
    print('Settings were updated')


def task3(settings):
    """
    Print settings.

    Args:
        settings (map): the settings

    The function prints the settings in alphabetical order.
    """
    settings_array = []
    for key in settings.keys():
        settings_array.append(key)
    # check sort and check print
    settings_array.sort()
    for current_setting in settings_array:
        print(current_setting, ': ', settings[current_setting], sep='')


total_games_index = 0
win_rate_index = 1
avg_tries_index = 2
total_wins_index = 3
total_tries_index = 4
add_increment = 1
starting_value = 0


def update_players(name, count, win, players):
    """
    Update stats.

    The function updates the stats after the game.

    Args:
        players (map): the scoreboard
        name (string): the name of the player.
        count (int): the number of guesses made by the player.
        win (int): true if the player won the game else false.
    """
    if name in players.keys():
        if win == int(True):
            # total wins
            players[name][total_wins_index] += add_increment
            # total guesses
            players[name][total_tries_index] += count
        # total games
        players[name][total_games_index] += add_increment
        # avg wins
        players[name][win_rate_index] = (players[name][total_wins_index] / players[name][total_games_index]) * 100
        # avg guesses per win
        if players[name][total_wins_index] != int(False):
            players[name][avg_tries_index] = players[name][total_tries_index] / players[name][total_wins_index]
    else:
        if win == int(True):
            players[name] = [add_increment, 100, count, int(True), count]
        else:
            players[name] = [add_increment, starting_value, starting_value, starting_value, starting_value]


def check_word_in_file(word, settings):
    """
    Check word.

    The function checks if the word is in the file.

    Args:
        settings (map): the settings
        word (string): the word to check.

    Returns:
        bool: true if the word is in the file else false.
    """
    with open(settings['file_path'], 'r') as words:
        words_list = words.read().splitlines()
        return word in words_list


def task2(players, settings):
    """
     Play game.

     Args:
        players (map): the scoreboard
        settings (map): the settings

    The function plays out the game Wordle by the format
    specified by the assignment.
    at the end of the game it updates the player's stats.
    """
    name = input("Enter player's name:\n")
    the_word = input('Enter a word:\n')
    # checks if the word is valid
    if check_word_in_file(the_word, settings) == int(False):
        print("That's not a word!")
        return
    if len(the_word) != int(settings['word_length']):
        print('That word is the wrong length!')
        return
    # starts the game
    print('Welcome to Wordle! You have', settings['tries'], 'tries to guess the word.')
    print('The word is', settings['word_length'], 'letters long.')
    tries_limit = int(settings['tries'])
    index = 0
    win = 0
    guesses = {}
    while index < tries_limit and win == int(False):
        # gets a gues from the user
        word_guess = input('Guess a word:\n')
        # checks if the word is valid
        if check_word_in_file(word_guess, settings) == int(False):
            print('Invalid guess')
            continue
        if len(word_guess) != int(settings['word_length']):
            print('Invalid guess')
            continue
        # documents the result of the guess
        guesses[index] = ''
        for index2 in range(len(word_guess)):
            if word_guess[index2] == the_word[index2]:
                guesses[index] += word_guess[index2]
            elif word_guess[index2] in the_word:
                guesses[index] += '+'
            else:
                guesses[index] += '-'
        # prints the result of the guess
        print(guesses[index])
        if guesses[index] == the_word:
            print('You win!')
            win = int(True)
        index += add_increment

    count_guesses = 0
    if win == int(False):
        print('You lost! The word was', the_word)
    print('Game over!')
    # prints the total guesses results
    for index3 in range(len(guesses)):
        print(guesses[index3])
        count_guesses += add_increment
    # updating/ adding to players
    update_players(name, count_guesses, win, players)


stats_index = 1


def task4(players):
    """
    Print scoreboard.

    Args:
        players (map): the scoreboard

    The function prints the scoreboard (per player):
    name , win rate, and average tries.
    the scoreboard is printed by highest win rate and if it's equal then by name.
    """
    # sorts the array by players win rate and if it's equal then by name
    players_array = sorted(players.items(), key=lambda player: (-player[stats_index][win_rate_index], player[0]))
    print('Scoreboard:')
    # prints the scoreboard
    for current_player in players_array:
        avg_wins = '{:.2f}'.format(float(current_player[stats_index][win_rate_index]))
        avg_guesses_win = '{:.2f}'.format(float(current_player[stats_index][avg_tries_index]))
        # checks if the player never won haha
        if avg_guesses_win == '0.00':
            avg_guesses_win = 'NaN'
        print(current_player[0], ': ', current_player[stats_index][total_games_index], ' games, ', end='', sep='')
        print(avg_wins, '% win rate, ', avg_guesses_win, ' average tries', sep='')


def execute_task(task_number, players, settings):
    """
    Get task number.

    The function gets a task number and executes the task accordingly.

    Args:
        players (map): the scoreboard
        settings (map): the settings
        task_number (string): the chosen task to execute.
    """
    if task_number == '1':
        task1(settings)
    elif task_number == '2':
        task2(players, settings)
    elif task_number == '3':
        task3(settings)
    elif task_number == '4':
        task4(players)
    elif task_number == '0':
        return
    else:
        print('Invalid option')


def main():
    """
    Get input.

    The function gets an input from the user until he chooses 0
    and executes the tasks.
    """
    # the default settings
    settings = {'tries': '6', 'word_length': '5', 'file_path': 'words.txt'}
    players = {}
    task_number = '2'
    while task_number != '0':
        task_number = menu()
        execute_task(task_number, players, settings)


if __name__ == '__main__':
    main()
