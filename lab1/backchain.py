from production import AND, OR, NOT, PASS, FAIL, IF, THEN, \
     match, populate, simplify, variables
from zookeeper import ZOOKEEPER_RULES

# This function, which you need to write, takes in a hypothesis
# that can be determined using a set of rules, and outputs a goal
# tree of which statements it would need to test to prove that
# hypothesis. Refer to the problem set (section 2) for more
# detailed specifications and examples.

# Note that this function is supposed to be a general
# backchainer.  You should not hard-code anything that is
# specific to a particular rule set.  The backchainer will be
# tested on things other than ZOOKEEPER_RULES.


def backchain_to_goal_tree(rules, hypothesis):
	or_conditionals=[hypothesis]
	for rule in rules:
		for consequent in list(rule.consequent()):
			matches = match(consequent,hypothesis)
			if matches!=None:
				antecedent = rule.antecedent()
				if isinstance(antecedent,AND) or isinstance(antecedent,OR):
					sub_tree  = [backchain_to_goal_tree(rules,populate(element,matches)) for element in list(antecedent)]
					if isinstance(antecedent,AND):
						or_conditionals.append(AND(sub_tree))
					else:
						or_conditionals.append(OR(sub_tree))
				else:
					or_conditionals.append(backchain_to_goal_tree(rules,populate(antecedent,matches)))
	return simplify(OR(or_conditionals))
	raise NotImplementedError

# Here's an example of running the backward chainer - uncomment
# it to see it work:
# print backchain_to_goal_tree(ZOOKEEPER_RULES, 'opus is a penguin')
