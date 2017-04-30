library(RCurl)
library(caret)


# NIPS (Neural Information Processing Systems) 2013 competition differentiating between two handwritten digits. 
# Download data from the UC Irvine Machine Learning Repository 

urlfile = "https://archive.ics.uci.edu/ml/machine-learning-databases/gisette/GISETTE/gisette_train.data"
x = getURL(urlfile, ssl.verifypeer = FALSE)
gisetteRaw = read.table(textConnection(x), sep='', header=FALSE, stringsAsFactors=FALSE)

# labels file contains truth (i.e., which digit is actually represented)
urlfile = "https://archive.ics.uci.edu/ml/machine-learning-databases/gisette/GISETTE/gisette_train.labels"
x = getURL(urlfile, ssl.verifypeer = FALSE)
g_labels = read.table(textConnection(x), sep='', header=FALSE, stringsAsFactors=FALSE)

dim(gisetteRaw)
# limit the data set for in-class demonstration
gisetteRaw = gisetteRaw[,1:500]


### check to see if any features have zero (or near-zero) variation

nzv = nearZeroVar(gisetteRaw, saveMetrics = TRUE)
head(nzv)
range(nzv$percentUnique)

### consider removing variables with low variation?
### when would you want to keep variables with low variation? 
ncol(gisetteRaw)
nrow(nzv[nzv$percentUnique > 0.1,])
gisette_nzv = gisetteRaw[c(rownames(nzv[nzv$percentUnique > 0.1,]))]



########### PCA ###########

# R function prcomp to conduct principal components analysis
# NOTE: remember to scale the data!
pmatrix = scale(gisette_nzv)
dim(pmatrix)
princ = prcomp(pmatrix)
screeplot(princ, length(princ$sdev))
screeplot(princ,100)
summary(princ)$importance
