import subprocess
import sys
import threading
import time

ALL_TESTS = """
# Part A
# showcase friendship
# [Expected output]
# Mike -> PrimaryUser -> George 
# George -> Mike -> Allen
# Allen -> George -> Andrew
# Hunter -> PrimaryUser
# Andrew -> Allen
# PrimaryUser -> Mike -> Hunter -> Michelle -> Michael
# Michelle -> PrimaryUser
# Michael -> PrimaryUser
add user Mike
add user George
add user Allen
add user Hunter
add user Andrew
add user Michelle
add user Michael
friend Mike
friend Mike George
friend George Allen
friend Allen Andrew
friend Allen
friend Michelle
friend Michael
break Allen
friend Allen Hunter
break Allen Hunter
friend Hunter

show friends\nMike
show friends\nGeorge
show friends\nAllen
show friends\nHunter
show friends\nAndrew
show friends\nPrimaryUser
show friends\nMichelle
show friends\nMichael
exit

%%%
# Part B
#  showcase adding songs and system/primaryuser library
# [Expected outcome]
# Alone and Panda in PrimaryUser Library
# VIBEZ and other songs in the system library
# VIBEZ playcount 50
# Panda playCount 70
# remove song from panda
# Panda playcount 0

# B1 - adds songs and then outputs them once added into the system library
add song VIBEZ
add song Alone
add song Panda
add song Grape
add song Vine
show unadded

# B2 - listens to song and should add 'Alone' and 'Panda' to user library
listen\nPrimaryUser\nVIBEZ\n50
listen\nPrimaryUser\nAlone\n100
listen\nPrimaryUser\nPanda\n70
recommend 2
show added

# B3 - 'VIBEZ' should still have playCount of 50, 'Panda' should have playCount of 0, unadded should output 'VIBEZ', 'Grape', and 'Vine'
show unadded
show playCount\nVIBEZ
show playCount\nPanda

# B4 - Removes Panda from user library, shows that it's back in system library with playCount = 0
remove song Panda
show added
show unadded
show playCount\nPanda
exit

%%%
# Tracking Listens
# [FriendShip Structure and their radius]
# 1 Mike -> PrimaryUser -> George
# 2 George -> Mike -> Allen
# 3 Allen -> George -> Andrew
# 1 Hunter -> PrimaryUser
# 4 Andrew -> Allen
# 0 PrimaryUser -> Mike -> Hunter -> Michelle -> Michael
# 1 Michelle -> PrimaryUser
# 1 Michael -> PrimaryUser

# C1 - Adds friends, and shows friendships specified above
add user Mike
add user George
add user Allen
add user Hunter
add user Andrew
add user Michelle
add user Michael
friend Mike
friend Mike George
friend George Allen
friend Allen Andrew
friend Allen
friend Michelle
friend Michael
break Allen
friend Allen Hunter
break Allen Hunter
friend Hunter
radius 2
show friends\nMike
show friends\nGeorge
show friends\nAllen
show friends\nHunter
show friends\nAndrew
show friends\nPrimaryUser
show friends\nMichelle
show friends\nMichael

add song VIBEZ
add song Alone
add song Panda
add song Grape
add song Vine

# 1 Mike -> PrimaryUser -> George
# 2 George -> Mike -> Allen
# 3 Allen -> George -> Andrew
# 1 Hunter -> PrimaryUser
# 4 Andrew -> Allen
# 0 PrimaryUser -> Mike -> Hunter -> Michelle -> Michael
# 1 Michelle -> PrimaryUser
# 1 Michael -> PrimaryUser

# C2
# [expected outcome]
# Title: VIBEZ    Listens: 70
# Title: Alone    Listens: 20
# Title: Vine    Listens: 50
# Title: Panda    Listens: 30
# Title: Grape    Listens: 40
# the following will get recorded
listen\nMike\nVIBEZ\n10
listen\nHunter\nAlone\n20
listen\nMichelle\nPanda\n30
listen\nMichael\nGrape\n40
listen\nMichelle\nVine\n50
listen\nGeorge\nVIBEZ\n60

# C3
# the following are out of range
listen\nAllen\nAlone\n100
listen\nAndrew\nVIBEZ\n100

show unadded
exit

%%%
#making recommendation

# D1 - prints out all songs that are added and listened to
add song OneDay
listen\nPrimaryUser\nOneDay\n11
add song TakeOnMe
listen\nPrimaryUser\nTakeOnMe\n21
add song 7Years
listen\nPrimaryUser\n7Years\n31
add song What'sNext
listen\nPrimaryUser\nWhat'sNext\n41
add song CallingMyPhone
listen\nPrimaryUser\nCallingMyPhone\n51
add song WantsAndNeeds
listen\nPrimaryUser\nWantsAndNeeds\n61
add song Whoopty
listen\nPrimaryUser\nWhoopty\n71
add song Practice
listen\nPrimaryUser\nPractice\n81
add song BigBadWolf
listen\nPrimaryUser\nBigBadWolf\n91
add song Verpennt
listen\nPrimaryUser\nVerpennt\n101
add song LowLife
listen\nPrimaryUser\nLowLife\n111
add song RunItUp
listen\nPrimaryUser\nRunItUp\n121
add song Gangsta'sParadise
listen\nPrimaryUser\nGangsta'sParadise\n131
add song VIBEZ
listen\nPrimaryUser\nVIBEZ\n141
add song Angekommen
listen\nPrimaryUser\nAngekommen\n151
add song AllesNachPlan
listen\nPrimaryUser\nAllesNachPlan\n161
add song LeereHande
listen\nPrimaryUser\nLeereHande\n171
add song SpielEinSpiel
listen\nPrimaryUser\nSpielEinSpiel\n181
add song WennDasSchicksalTrifft
listen\nPrimaryUser\nWennDasSchicksalTrifft\n191
add song UneJam
listen\nPrimaryUser\nUneJam\n201
add song Extasy
listen\nPrimaryUser\nExtasy\n211
add song Elmas
listen\nPrimaryUser\nElmas\n221
add song DuBistDerFehler
listen\nPrimaryUser\nDuBistDerFehler\n231
add song OhneDich
listen\nPrimaryUser\nOhneDich\n241
add song UnterVerdacht
listen\nPrimaryUser\nUnterVerdacht\n251
add song Paradies
listen\nPrimaryUser\nParadies\n261
add song Madonna
listen\nPrimaryUser\nMadonna\n271
add song Angst
listen\nPrimaryUser\nAngst\n281
add song Asphalt&Tennissocken
listen\nPrimaryUser\nAsphalt&Tennissocken\n291
add song DieseEineMelodie
listen\nPrimaryUser\nDieseEineMelodie\n301

show unadded

# D2 - recommends 7 most played songs, adding them to user library, and setting their playCount to 0
# they are: DieseEineMelodie, Asphalt&Tennissocken, Angst, Madonna, Paradies, UnterVerdacht, OhneDich

recommend 2
recommend 3
recommend 2
show added
show unadded
show playCount\nDieseEineMelodie
show playCount\nAsphalt&Tennissocken
show playCount\nAngst
show playCount\nMadonna
show playCount\nParadies
show playCount\nUnterVerdacht
show playCount\nOhneDich
show playCount\nDuBistDerFehler

# D3 - increases playCount by 1000
listen\nPrimaryUser\nDuBistDerFehler\n1000
show playCount\nDuBistDerFehler


exit
"""

enable_colors = True

RED = "\033[91m"
GREEN = "\033[92m"
BLUE = "\033[94m"
AQUA = "\033[0;36m"
ENDC = "\033[0m"


def reader(stream):
    while True:
        c = stream.read(1)
        print(c, end="", flush=True)


def run(program, test_choice: int, speed: float):
    p = subprocess.Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    t = threading.Thread(target=reader, args=[p.stdout], daemon=True)
    t.start()

    tests = ALL_TESTS.split("%%%")
    if test_choice < 0 or test_choice >= len(tests):
        print(f"Invalid test: f{test_choice}")
        exit(1)
    test = tests[test_choice]
    lines = [x for x in test.splitlines() if x.strip()]

    start = 0
    while start < len(lines):
        line = lines[start]
        if line.startswith('#'):
            print(BLUE + line + ENDC, flush=True)
            start += 1
        else:
            break

    time.sleep(5 * speed)
    for i in range(start, len(lines)):
        line = lines[i]
        print(GREEN + line + ENDC if enable_colors else line, flush=True)
        p.stdin.write(line + "\n")
        p.stdin.flush()
        time.sleep(speed)
    p.wait()


def main():
    args = sys.argv[1:]
    if 2 <= len(args) <= 3:
        program = args[0]
        test_choice = args[1]
        test_choice = int(test_choice[1:] if test_choice.startswith('t') else test_choice)
        speed = 0.1 if len(args) < 3 else (1 / (10 * float(args[2])))
        run(['./' + program], test_choice, speed)
        # loop.run_until_complete(run(['stdbuf', '-i0', ' -o0', '-e0', f'./{args[0]}']))
    else:
        print(f"Usage: python3 tester.py <executable> <test> [speed]")


if __name__ == '__main__':
    main()

"""
Notes:
Playlists won't contain whitespaces
"""
