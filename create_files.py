"""create_files.py - Creates files to play laser tag game

SYNOPSIS:
    A script that creates two team files and a corresponding
    match file. The player names are randomly selected along
    with the time for the tagger to tag the target.

"""

from faker import Faker
from random import choice
from random import randint
from datetime import datetime

__author__ = 'psaajc1420@gmail.com (Cadena, Jacob)'


def find_players(team1_size, team2_size):
    """Creates two players on different teams.

    Creates two players randomly and makes sure
    they are not the same.

    Args:
        team1_size: The number of players on team 1
        team2_size: The number of players on team 2

    Returns:
        A list that contains the ids of the players for each
        team. The first element correpsonds to the first team's id number
        which can range from 0 to 9. The second element correpsonds to
        the second team's number which can range from 10 to 19.
        For example:

        -> [1, 11]
        -> [9, 19]
        -> [0, 15]

    Raises:
        None
    """

    players = [0, 0]
    while players[0] == players[1]:
        players[0] = randint(0, team1_size-1)
        players[1] = randint(team1_size, team1_size + team2_size - 1)

    rand_num = randint(0, 100)
    if rand_num >= 50:
        players[0], players[1] = players[1], players[0]

    return players


def create_match_file(num_players):
    """Creates a match file for laser tag.

    Creates a match files based on the number of tags given by
    the users's input. In particular, player ids are found
    for each time corresponding to the target and tagger id;
    the time elapsed for each tag; the location id specifying
    the location of the tag (back, shoulder, etc.).


    Args:
        file_name: The name of the match file.
        num_players: The number of players for each team
            given in a list.

    Returns:
        None

    Raises:
        None
    """

    file_name = input("\nEnter the file name for the match: ")
    total_tags = input("How many tags do you want to simulate: ")

    start_time = datetime.now().microsecond
    with open(file_name, "w") as file:
        file.write(total_tags+"\n")
        total_tags = int(total_tags)
        for _ in range(total_tags):
            players = find_players(num_players[0], num_players[1])
            location_id = randint(1, 4)
            time_elapsed = datetime.now().microsecond - start_time
            file.write("{} {} {} {}\n".format(players[0], players[1],
                                              time_elapsed, location_id))


def make_ordinal(num):
    """Finds the ordinal representation of a number.

    Args:
        num: The number to convert to ordinal

    Returns:
        ordinal_num: the ordinal reprsentation of the number given.

    Raises:
        None
    """

    remainder = num % 10
    ordinal_num = ""
    num = str(num)
    if num == 1 or remainder == 1:
        ordinal_num = num + "st"
    elif num == 2 or remainder == 2:
        ordinal_num = num + "nd"
    elif num == 3 or remainder == 3:
        ordinal_num = num + "rd"
    else:
        ordinal_num = num + "th"

    return ordinal_num


def get_team_info(num_teams):
    """Gains the team information from the user.

    Finds the team names and the number of players for
    each team depending on the number of teams.


    Args:
        num_teams: The number of teams playing laser tag

    Returns:
        A tuple that consists of two lists. The first list contains
        the team names and the second list contains number of players
        for each team in a list.

    Raises:
        None
    """

    team_names = []
    num_players = []
    for team in range(1, num_teams+1):
        text = (
            "\nWhat's the name of "
            "the {} team: "
        ).format(make_ordinal(team))
        team_name = input(text)
        team_names.append(team_name)
        text = (
            'How many players(1-10) are '
            'playing tag for the {}: '
        ).format(team_name)
        num_players.append(int(input(text)))

    return team_names, num_players


def create_team_files():
    """Creates the team files.

    Creates each team file and then returns the list of
    the number of players.

    Args:
        None

    Returns:
        A list of the number of players

    Raises:
        None
    """

    faker = Faker()

    num_teams = int(input("Enter the number of teams: "))
    team_names, num_players = get_team_info(num_teams)

    file_names = ['{}.txt'.format(name.lower()) for name in team_names]

    id_num = 0
    for i, file_name in enumerate(file_names):
        with open(file_name, "w") as file:
            file.write("The " + team_names[i] + "\n")
            file.write("{}\n".format(num_players[i]))
            for _ in range(num_players[i]):
                # pylint: disable=no-member
                name = faker.first_name()
                file.write("{} {}\n".format(id_num, name))
                id_num += 1

    return num_players

if __name__ == "__main__":

    num_players = create_team_files()
    create_match_file(num_players)
