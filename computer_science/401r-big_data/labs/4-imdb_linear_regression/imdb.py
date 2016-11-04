import pandas as pd
import numpy as np
from pandas import Series, DataFrame
import matplotlib.pylab as plt
import statsmodels.formula.api as smf
from sklearn.cross_validation import train_test_split
import statsmodels.api as sm
from sklearn.linear_model import LassoLarsCV

 
### Print the Full Model
movieData = pd.read_csv("IMDb.csv")
movieData.dropna()
print movieData.head()

print'\n\n-------------------\n\n'

### split data into training, test
movieData = pd.read_csv("IMDb.csv", na_values=["."])
movieData = movieData.dropna()

# splits data set by a random 30 / 70 %
movieTrain, movieTest = train_test_split(movieData, test_size=.3, random_state=123)
movieTrain.shape
movieTrain.shape


### Basic linear regression (without variable selection)
model = smf.ols(formula='gross ~ 1 + C(color) + duration + director_facebook_likes + \
                        actor_3_facebook_likes + actor_1_facebook_likes + \
                        cast_total_facebook_likes + facenumber_in_poster + budget + \
                        title_year + actor_2_facebook_likes', data=movieTrain).fit()

'''
Values removed: 
- C(language)
- C(country)
- C(content_rating)
'''

print model.summary()

print'\n\n-------------------\n\n'

# recode1 = {-1:0, 0:0, 1:1}
# movieData['color'] = movieData.color.map(recode1)

predvar = movieData[['gross', 'duration', 'director_facebook_likes',
                        'actor_3_facebook_likes', 'actor_1_facebook_likes',
                        'cast_total_facebook_likes', 'facenumber_in_poster',
                        'budget', 'title_year', 'actor_2_facebook_likes']]
target = movieData.gross
predictors = predvar.copy()

pred_train, pred_test, resp_train, resp_test = train_test_split(
                                    predictors, target, test_size=.3, random_state=123)

# specify the lasso regression model -- or this
# precompute=True helpful for large data sets
model = LassoLarsCV(cv=10, precompute=True).fit(pred_train,resp_train) # the actual LASSO call, where your model is pulled out

# print variable names and regression coefficients -- or this
# note: we standardized variables so we can look at size of coefficients to assess which variables have the most predictive power
dict(zip(predictors.columns, model.coef_))

# plot coefficient progression
# note: Python refers to LASSO penalty (i.e, tuning) parameter as alpha
# note: apply -log(10) transformation to alpha values simply to make them easier to read
m_log_alphas = -np.log10(model.alphas_)
ax = plt.gca() # set up axes
plt.plot(m_log_alphas, model.coef_path_.T) # alpha on x axis, change in regression coefficients on y axis
plt.axvline(-np.log10(model.alpha_), linestyle='--', color='k',
            label='alpha CV') # plot black dashed line at alpha value ultimately selected
plt.ylabel('Regression Coefficients')
plt.xlabel('-log(alpha)')
plt.title('Regression Coefficients Progression for Lasso Paths')
plt.savefig('Fig01')

# plot mean square error for each fold
m_log_alphascv = -np.log10(model.cv_alphas_)
plt.figure()
plt.plot(m_log_alphascv, model.cv_mse_path_, ':')
plt.plot(m_log_alphascv, model.cv_mse_path_.mean(axis=-1), 'k',
         label='Average across the folds', linewidth=2)
plt.axvline(-np.log10(model.alpha_), linestyle='--', color='k',
            label='alpha CV')
plt.legend()
plt.xlabel('-log(alpha)')
plt.ylabel('Mean squared error')
plt.title('Mean squared error on each fold')
plt.savefig('Fig02')
         

# MSE from training and test data
from sklearn.metrics import mean_squared_error
from sklearn.metrics import silhouette_samples
train_error = mean_squared_error(resp_train, model.predict(pred_train))
test_error = mean_squared_error(resp_test, model.predict(pred_test))
print ('training data MSE')
print(train_error)
print ('test data MSE')
print(test_error)

# R-square from training and test data
rsquared_train=model.score(pred_train,resp_train)
rsquared_test=model.score(pred_test,resp_test)
print ('training data R-square')
print(rsquared_train)
print ('test data R-square')
print(rsquared_test)

print(silhouette_samples(resp_train, model.predict(pred_train)))