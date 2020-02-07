 game: menu.cpp macros.h colors.h colors.o tile.h tile.o map.h map.o skirmish.h skirmish.o entity.h entity.o civilization.h civilization.o bonus.h bonus.o player.h player.o building_templates.h building_templates.o unit_templates.h unit_templates.o unit_commands.h unit_commands.o combat.o technology.h technology.o building_commands.h building_commands.o
	g++ menu.cpp colors.o tile.o map.o skirmish.o entity.o civilization.o bonus.o player.o building_templates.o unit_templates.o unit_commands.o combat.o technology.o building_commands.o -o game -lncurses

colors.o: colors.cpp
	g++ -c colors.cpp -Wall -Werror -g -o colors.o

tile.o: tile.cpp
	g++ -c tile.cpp -Wall -Werror -g -o tile.o

map.o: map.cpp
	g++ -c map.cpp -Wall -Werror -g -o map.o

skirmish.o: skirmish.cpp
	g++ -c skirmish.cpp -Wall -Werror -g -o skirmish.o

entity.o: entity.cpp
	g++ -c entity.cpp -Wall -Werror -g -o entity.o

civilization.o: civilization.cpp
	g++ -c civilization.cpp -Wall -Werror -g -o civilization.o

bonus.o: bonus.cpp
	g++ -c bonus.cpp -Wall -Werror -g -o bonus.o

player.o: player.cpp
	g++ -c player.cpp -Wall -Werror -g -o player.o

building_templates.o: building_templates.cpp
	g++ -c building_templates.cpp -Wall -Werror -g -o building_templates.o

unit_templates.o: unit_templates.cpp
	g++ -c unit_templates.cpp -Wall -Werror -g -o unit_templates.o

unit_commands.o: unit_commands.cpp
	g++ -c unit_commands.cpp -Wall -Werror -g -o unit_commands.o

combat.o: combat.cpp
	g++ -c combat.cpp -Wall -Werror -g -o combat.o

technology.o: technology.cpp
	g++ -c technology.cpp -Wall -Werror -g -o technology.o

building_commands.o: building_commands.cpp
	g++ -c building_commands.cpp -Wall -Werror -g -o building_commands.o

clean:
	rm -f colors.o tile.o map.o skirmish.o entity.o civilization.o bonus.o player.o building_templates.o unit_templates.o unit_commands.o combat.o technology.o building_commands.o valgrind.log *~
