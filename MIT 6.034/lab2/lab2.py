# Fall 2012 6.034 Lab 2: Search
#
# Your answers for the true and false questions will be in the following form.  
# Your answers will look like one of the two below:
#ANSWER1 = True
#ANSWER1 = False

# 1: True or false - Hill Climbing search is guaranteed to find a solution
#    if there is a solution
ANSWER1 = False

# 2: True or false - Best-first search will give an optimal search result
#    (shortest path length).
#    (If you don't know what we mean by best-first search, refer to
#     http://courses.csail.mit.edu/6.034f/ai3/ch4.pdf (page 13 of the pdf).)
ANSWER2 = False

# 3: True or false - Best-first search and hill climbing make use of
#    heuristic values of nodes.
ANSWER3 = True

# 4: True or false - A* uses an extended-nodes set.
ANSWER4 = True

# 5: True or false - Breadth first search is guaranteed to return a path
#    with the shortest number of nodes.
ANSWER5 = True

# 6: True or false - The regular branch and bound uses heuristic values
#    to speed up the search for an optimal path.
ANSWER6 = False

# Import the Graph data structure from 'search.py'
# Refer to search.py for documentation
from search import Graph

## Optional Warm-up: BFS and DFS
# If you implement these, the offline tester will test them.
# If you don't, it won't.
# The online tester will not test them.

def bfs(graph, start, goal):
	if start==goal:
		return [start]
	path = []
	extended_list=[]
	queue=[[start]]
	while True:
		if queue==[]:
			break
		new_nodes = graph.get_connected_nodes(queue[0][-1])
		extended_list.extend([queue[0][-1]])
		if goal in new_nodes:
			path = queue[0]+[goal]
			break
		for node in new_nodes:
			if not node in queue[0] and not node in extended_list:
				queue += [queue[0]+[node]]
		queue.pop(0)
	return path
	raise NotImplementedError

## Once you have completed the breadth-first search,
## this part should be very simple to complete.
def dfs(graph, start, goal):
	if start==goal:
		return [start]
	path = []
	extended_list=[]
	stack=[[start]]
	while True:
		if stack==[]:
			break
		new_nodes = graph.get_connected_nodes(stack[-1][-1])
		extended_list.extend([stack[-1][-1]])
		if goal in new_nodes:
			path = stack[-1]+[goal]
			break
		base_node = stack[-1]
		stack.pop(-1)
		for node in new_nodes:
			if not node in base_node and not node in extended_list:
				stack = stack+[base_node+[node]]
	return path
	raise NotImplementedError


## Now we're going to add some heuristics into the search.  
## Remember that hill-climbing is a modified version of depth-first search.
## Search direction should be towards lower heuristic values to the goal.
def hill_climbing(graph, start, goal):
	def heuristic(node):
		return graph.get_heuristic(node,goal)
	if start==goal:
		return [start]
	path = []
	stack=[[start]]
	while True:
		#print stack
		if stack==[]:
			break
		new_nodes = graph.get_connected_nodes(stack[-1][-1])
		if goal in new_nodes:
			path = stack[-1]+[goal]
			break
		base_node = stack[-1]
		stack.pop(-1)
		new_nodes = sorted(new_nodes,key=heuristic,reverse=True)
		for node in new_nodes:
			if not node in base_node:
				stack = stack+[base_node+[node]]
	return path
	raise NotImplementedError

## Now we're going to implement beam search, a variation on BFS
## that caps the amount of memory used to store paths.  Remember,
## we maintain only k candidate paths of length n in our agenda at any time.
## The k top candidates are to be determined using the 
## graph get_heuristic function, with lower values being better values.
def beam_search(graph, start, goal, beam_width):
	def heuristic(path):
		return graph.get_heuristic(path[-1],goal)
	if start==goal:
		return [start]
	path = []
	extended_list=[]
	queue=[[start]]
	while True:
		if queue==[]:
			break
		if len(queue[0])==len(queue[-1]):
			#path lengths are the same
			queue = sorted(queue,key=heuristic)[0:beam_width]
		new_nodes = graph.get_connected_nodes(queue[0][-1])
		extended_list.extend([queue[0][-1]])
		if goal in new_nodes:
			path = queue[0]+[goal]
			break
		for node in new_nodes:
			if not node in queue[0]:
				queue += [queue[0]+[node]]
		queue.pop(0)
	return path
	raise NotImplementedError

## Now we're going to try optimal search.  The previous searches haven't
## used edge distances in the calculation.

## This function takes in a graph and a list of node names, and returns
## the sum of edge lengths along the path -- the total distance in the path.
def path_length(graph, node_names):
	length=0
	for i in range(0,len(node_names)-1):
		length=length+graph.get_edge(node_names[i],node_names[i+1]).length
	return length
	raise NotImplementedError


def branch_and_bound(graph, start, goal):
	def get_path_len(node_names):
		return path_length(graph,node_names)
	if start==goal:
		return [start]
	path = []
	path_len=1000000
	stack=[[start]]
	while True:
		if path!=[]:
			stack_len = len(stack)
			for i in range(stack_len-1,0,-1):
				if path_length(graph,stack[i])>path_len:
					stack.pop(i)
		if stack==[]:
			break
		new_nodes = graph.get_connected_nodes(stack[-1][-1])
		base_node = stack[-1]
		if goal in base_node:
			path=base_node
			break
		stack.pop(-1)
		for node in new_nodes:
			if not node in base_node:
				stack = stack+[base_node+[node]]
		stack = sorted(stack,key=get_path_len,reverse=True)
	return path
	raise NotImplementedError


def a_star(graph, start, goal):
	def get_len(node_names):
		return path_length(graph,node_names)+graph.get_heuristic(node_names[-1],goal)
	if start==goal:
		return [start]
	path = []
	extended_list=[]
	stack=[[start]]
	while True:
		if path!=[]:
			print path
			stack_len = len(stack)
			for i in range(stack_len-1,0,-1):
				if path_length(graph,stack[i])>path_len:
					stack.pop(i)
		if stack==[]:
			break
		new_nodes = graph.get_connected_nodes(stack[-1][-1])
		extended_list+=[stack[-1][-1]]
		base_node = stack[-1]
		if goal in base_node:
			path=base_node
			break
		stack.pop(-1)
		for node in new_nodes:
			if not node in base_node and node not in extended_list:
				stack = stack+[base_node+[node]]
		stack = sorted(stack,key=get_len,reverse=True)
	return path
	raise NotImplementedError


## It's useful to determine if a graph has a consistent and admissible
## heuristic.  You've seen graphs with heuristics that are
## admissible, but not consistent.  Have you seen any graphs that are
## consistent, but not admissible?

def is_admissible(graph, goal):
	isAdmissable=True
	for node in graph.nodes:
		if graph.get_heuristic(node,goal)>path_length(graph,a_star(graph,node,goal)):
			isAdmissable=False
			break
	return isAdmissable
	raise NotImplementedError

def is_consistent(graph, goal):
	isConsistent=True
	for node1 in graph.nodes:
		for node2 in graph.nodes:
			if abs(graph.get_heuristic(node1,goal)-graph.get_heuristic(node2,goal))>path_length(graph,a_star(graph,node1,node2)):
				isConsistent=False
				break
	return isConsistent
	raise NotImplementedError

HOW_MANY_HOURS_THIS_PSET_TOOK = '3'
WHAT_I_FOUND_INTERESTING = 'dfdf'
WHAT_I_FOUND_BORING = 'dfsd'
