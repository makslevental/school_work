matrix_power = function(A,n) {
	A_new = A
	for (i in 2:n) {
		A_new = A_new %*% A
	}
	return(A_new)
}

# This is one way to define a transition matrix
P = c(0, 1, 0, 0, 0, 0)
P = rbind(P,c(1/5,0,4/5,0,0,0))
P = rbind(P,c(0,2/5,0,3/5,0,0))
P = rbind(P,c(0,0,3/5,0,2/5,0))
P = rbind(P,c(0,0,0,4/5,0,1/5))
P = rbind(P,c(0, 0, 0, 0, 1, 0))

# Here is another method, creating an empty matrix and
# adding non-zero entries one at a time
N = 6
P = matrix(rep(0,N*N),N,N)
P[1,2] = 1
P[2,1] = 1/5; P[2,3] = 4/5
P[3,2] = 2/5; P[3,4] = 3/5
P[4,3] = 3/5; P[4,5] = 2/5
P[5,4] = 4/5; P[5,6] = 1/5
P[6,5] = 1


print('This is P')
print(P)

print("After 20 steps here is the transition matrix")
P_20 = matrix_power(P,20)
print(P_20)

print("If the chain starts at 0 wp .3 and at 3 wp .7")
print("after 20 steps, its distribution is")
mu = c(0.3,0,0,0.7,0,0)
print(mu%*%P_20)