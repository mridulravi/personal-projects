How to Run?

Eight-puzzle


		g++ -O3 -o manhattan eight_puzzle_graph_generator.cpp               
		(currently heuristic is set to manhattan_heuristic - to change this make change in code function call)
		
		./manhattan < input3.txt > manhattan_input.txt 	                     
		(takes 10-15 mins)
		
		g++ -O3 -o astar a_star.cpp
		
		./astar < manhattan_input.txt > manhattan_output.txt


Missionary-Cannibal

		g++ -O3 -o missionary_cannibal_n_by_2 missionary_graph_generator.cpp
		(currently heuristic is set to n/2 - to change this make change in code function call)

		./missionary_cannibal > missionary_cannibal_n_by_2_input
		
		g++ -O3 -o astar a_star.cpp
		
		./astar < missionary_cannibal_n_by_2_input


For bidiresctional:

		g++ -O3 -o bidiresctional bidiresctional.cpp

		./bidiresctional < input2.txt

For everything else:


		g++ -O3 -o astar a_star.cpp

		./astar < input1.txt
