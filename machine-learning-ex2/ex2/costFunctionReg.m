function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
sum=0;
for i=2:size(theta)
sum=sum+theta(i,1)*theta(i,1);
endfor
h = sigmoid(X*theta);
lg = log(h);
one = ones(m,1);
J = -y'*lg-(one-y)'*log(one-h);
J = J/m + (lambda*sum)/(2*m)

grad = X'*(h-y);
grad = grad./m;
for i=2:size(theta)
	grad(i,1)=grad(i,1)+lambda*theta(i,1)/m;
endfor



% =============================================================

end
