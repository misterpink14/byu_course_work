-- ******* isPrime *******

isPrime :: Int -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime 2 = True
isPrime 3 = True
isPrime n 
    | mod n 2 == 0 = False
    | otherwise = isPrime_ n 2 5

isPrime_ :: Int -> Int -> Int -> Bool
isPrime_ n i w 
    | n => iSqrt i = True
    | mod n i == 0 = True
    | otherwise = isPrime_ n (i + w) w

iSqrt :: Int-> Int
iSqrt n = floor(sqrt(fromIntegral n))


-- ******* primes *******

primes :: [Int]
primes = 2 : 3 : 5 : 7 : filter isPrime [8..]


-- ******* isPrimeFast *******

isPrimeFast :: Int -> Bool
isPrimeFast x = isPrimeFast_ x 0

isPrimeFast_ :: Int -> Int -> Bool
isPrimeFast_ a b
    | (primesFast!!b) => iSqrt a = True
    | mod a (primesFast!!b) == 0 = False
    | otherwise = isPrimeFast_ a (b + 1)

primesFast :: [Int]
primesFast = 2 : 3 : 5 : 7 : filter isPrimeFast [8..]


-- ***************************


-- ******* lcsLength *******

lcsLength :: String -> String -> Int
lcsLength x y = lcs x y

lcs :: String -> String -> Int
lcs [] y = 0
lcs x [] = 0
lcs (x:xx) (y:yy) 
  | x == y = 1 + (lcs xx yy)
  | otherwise = largest (lcs (x:xx) yy) (lcs xx (y:yy))

largest :: Int -> Int -> Int
largest x y = if x > y then x else y
