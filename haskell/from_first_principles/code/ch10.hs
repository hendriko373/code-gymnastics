import Data.Time

data DatabaseItem = DbString String
                    | DbNumber Integer
                    | DbDate UTCTime
                    deriving (Eq, Ord, Show)

theDatabase :: [DatabaseItem]
theDatabase = [
    DbDate (UTCTime (fromGregorian 1911 5 1) (secondsToDiffTime 34123)),
    DbNumber 9001,
    DbString "Hello, world!",
    DbDate (UTCTime (fromGregorian 1921 5 1) (secondsToDiffTime 34123))]

filterDbData :: [DatabaseItem] -> [UTCTime]
filterDbData = foldr f [] 
    where 
        f (DbDate a) ys = a:ys
        f _ ys = ys

filterDbNumber :: [DatabaseItem] -> [Integer]
filterDbNumber = foldr f []
    where
        f (DbNumber a) ys = a:ys
        f _ ys = ys

mostRecent :: [DatabaseItem] -> UTCTime
mostRecent = maximum . filterDbData

sumDb :: [DatabaseItem] -> Integer
sumDb = sum . filterDbNumber

avgDb :: [DatabaseItem] -> Double
avgDb = avg . (map fromIntegral) . filterDbNumber 
        where
            avg xs = sum xs / fromIntegral ( length xs)

stops = "pbtdkg"
vowels = "aeiou"

f1 :: Char -> Char -> String -> [(Char, Char, Char)]
f1 x y [] = []
f1 x y (z:zs) = (x, y, z) : (f1 x y zs)

f2 :: Char -> String -> String -> [(Char, Char, Char)]
f2 x [] ys = []
f2 x (y:ys) zs = f1 x y zs ++ f2 x ys zs

f3 :: String -> String -> String -> [(Char, Char, Char)]
f3 [] ys zs = []
f3 (x:xs) ys zs = f2 x ys zs ++ f3 xs ys zs

f4 :: String -> String -> [(Char, Char, Char)]
f4 s1 s2 = f3 s1 s2 s1

f4' :: String -> String -> [(Char, Char, Char)]
f4' s1 s2 = filter (\(c, _, _) ->  c /= 'p') $ f4 s1 s2

myOr1 :: [Bool] -> Bool
myOr1 [] = False
myOr1 (x:xs) = if x == True then True else myOr1 xs

myOr2 :: [Bool] -> Bool
myOr2 [] = False
myOr2 (x:xs) = x || myOr2 xs

myOr3 :: [Bool] -> Bool
myOr3 = foldr (\x y -> if x == True then True else y) False

myOr4 :: [Bool] -> Bool
myOr4 = foldr (||) False

myAny1 :: (a -> Bool) -> [a] -> Bool
myAny1 pred [] = False
myAny1 pred (x:xs) = pred x || myAny1 pred xs

myAny2 :: (a -> Bool) -> [a] -> Bool
myAny2 pred = foldr (\x y -> pred x || y) False 

myAny3 :: (a -> Bool) -> [a] -> Bool
myAny3 pred = foldr ((||) . pred) False 

myElem1 :: Eq a => a -> [a] -> Bool
myElem1 e = foldr (\x y -> x == e || y) False

myElem2 :: Eq a => a -> [a] -> Bool
myElem2 e = foldr ((||) . (==) e) False

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter pred = foldr f []
            where f x = if pred x then (:) x else id

squish :: [[a]] -> [a]
squish = foldr (++) []

squishMap :: (a -> [b]) -> [a] -> [b]
squishMap f = foldr ((++) . f) []

squishAgain :: [[a]] -> [a]
squishAgain = squishMap id