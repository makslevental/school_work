# # ex1 .07. R
# set.seed (123)
# n <- 10 # far from the CLT
# T <- 1
# t <- seq (0 ,T , length =100)
# S <- cumsum (2 * ( runif ( n ) >0.5) -1)
# W <- sapply (t , function ( x ) ifelse ( n *x >0 , S [ n * x ] ,0))
# W <- as.numeric ( W ) / sqrt ( n )
# 
# plot (t ,W , type = "l" , ylim = c ( -1 ,1),col="red")
# n <- 100 # closer to the CLT
# S <- cumsum (2 * ( runif ( n ) >0.5) -1)
# W <- sapply (t , function ( x ) ifelse ( n *x >0 , S [ n * x ] ,0))
# W <- as.numeric ( W ) / sqrt ( n )
# lines (t ,W , lty =2,col="blue")
# n <- 1000 # quite close to the limit
# S <- cumsum (2 * ( runif ( n ) >0.5) -1)
# W <- sapply (t , function ( x ) ifelse ( n *x >0 , S [ n * x ] ,0))
# W <- as.numeric ( W ) / sqrt ( n )
# lines (t ,W , lty =3,col="green")
tikz('normal.tex', standAlone = TRUE, width=5, height=5)
x1 <- cumsum(rexp(50,rate = .2)) 
y1 <- cumsum(c(0,rep(1,50))) 
plot(stepfun(x1,y1),xlim = c(0,50),ylim=c(0,50),do.points = F, main="",col="red",xlab = "time",ylab="arrivals")
par(new=TRUE)
x2 <- cumsum(rexp(50,rate = .5)) 
plot(stepfun(x2,y1),xlim = c(0,50),ylim=c(0,50),do.points = F, main="",col="green", xlab="",ylab="")
par(new=TRUE)
x3 <- cumsum(rexp(50,)) 
plot(stepfun(x3,y1),xlim = c(0,50),do.points = F, main="",col="blue",xlab="",ylab="",ylim=c(0,50))
legend('topleft', c('bob','alice','max') , 
       lty=1, col=c('red', 'green', 'blue'), bty='n', cex=.75)