-- String processing

notThe :: String -> Maybe String
notThe s
    | s == "the" = Nothing
    | otherwise  = Just s

replaceThe :: String -> String
replaceThe s = unwords $ map (f . notThe) (words s)
    where
        f Nothing  = "a"
        f (Just w) = w

countTheBeforeVowel :: String -> Integer
countTheBeforeVowel s =
    f $ map notThe (words s)
    where 
        f [] = 0 
        f (Nothing:(Just (c:cs)):xs) 
            | isVowel c = 1 + f xs
            | otherwise = 0 + f xs
        f (_:xs) = 0 + f xs
        
isVowel :: Char -> Bool
isVowel c = or $ map ((==) c) ['a', 'u', 'i', 'o', 'e'] 

countVowels :: String -> Int
countVowels = length . (filter isVowel)

-- Natural numbers

data Nat
    = Zero
    | Succ Nat
    deriving (Eq, Show)

natToInteger :: Nat -> Integer
natToInteger Zero = 0
natToInteger (Succ n) = 1 + natToInteger n 

integerToNat :: Integer -> Maybe Nat
integerToNat n
    | n < 0     = Nothing
    | otherwise = Just $ toNat n
        where 
            toNat 0 = Zero
            toNat m = Succ $ toNat $ m - 1

-- Maybe library

isJust :: Maybe a -> Bool
isJust (Just a) = True
isJust _        = False

isNothing :: Maybe a -> Bool
isNothing = not . isJust

mayybee :: b -> (a -> b) -> Maybe a -> b
mayybee n _ Nothing  = n
mayybee _ f (Just a) = f a

fromMaybe :: a -> Maybe a -> a
fromMaybe n = mayybee n id

listToMaybe :: [a] -> Maybe a
listToMaybe []     = Nothing
listToMaybe (x:xs) = Just x

maybeToList :: Maybe a -> [a]
maybeToList Nothing  = []
maybeToList (Just x) = [x]

catMaybes :: [Maybe a] -> [a]
catMaybes = (map (\(Just a) -> a)) . (filter isJust)

flipMaybe :: [Maybe a] -> Maybe [a]
flipMaybe xs = 
    case length result == length xs of
        False -> Nothing
        True  -> Just result
        where result = catMaybes xs

-- Either library
isLeft :: Either a b -> Bool
isLeft (Left a) = True
isLeft _      = False

lefts' :: [Either a b] -> [a]
lefts' = 
    (foldr ((:) . (\(Left a) -> a)) [])
    . (filter isLeft)

rights' :: [Either a b] -> [b]
rights' = 
    (foldr ((:) . (\(Right b) -> b)) [])
    . (filter $ not . isLeft)

partitionEithers' :: [Either a b] -> ([a], [b])
partitionEithers' xs = (lefts' xs, rights' xs)

either' :: (b -> c) -> (a -> c) -> Either a b -> c
either' f _ (Right b) = f b
either' _ g (Left a)  = g a
     
eitherMaybe'' :: (b -> c) -> Either a b -> Maybe c
eitherMaybe'' f = either' (Just . f) (\a -> Nothing) 