module Main where

import Test.QuickCheck

-- Heavy lifting

a :: [Int]
a = fmap (+1) $ read "[1]" 

b :: Maybe [String]
b = (fmap . fmap) (++ "lol") (Just ["Hi,", "Hello"])

c :: Integer -> Integer
c = fmap (*2) (\x -> x - 2)

d :: (Num a, Enum a, Show a) => a -> String
d = fmap ((return '1' ++) . show) (\x -> [x, 1..3])

e :: IO Integer
e = let ioi = readIO "1" :: IO Integer
        changed = fmap read $ fmap ("123" ++) $ fmap show ioi
    in fmap (*3) changed

-- Check functor laws

functorId :: (Functor f, Eq (f a)) => f a -> Bool
functorId fa = fmap id fa == fa

functorComp :: (Functor f, Eq (f c)) =>
                      (f a)
                   -> Fun a b
                   -> Fun b c
                   -> Bool
functorComp fa (Fun _ f) (Fun _ g) = 
  fmap (g . f) fa == (fmap g . fmap f) fa


-- Instances of Functor

--1
newtype Identity a = Identity a
  deriving (Show, Eq)

instance Functor Identity where
  fmap f (Identity a) = Identity $ f a

instance Arbitrary a => Arbitrary (Identity a) where
  arbitrary = do
    a <- arbitrary
    return $ Identity a

--2
data Pair a = Pair a a
  deriving (Show, Eq)

instance Functor Pair where
  fmap f (Pair x y) = Pair (f x) (f y)

instance Arbitrary a => Arbitrary (Pair a) where
  arbitrary = do
    x <- arbitrary
    y <- arbitrary
    return $ Pair x y

--3
data Two a b = Two a b deriving (Show, Eq)

instance Functor (Two r) where
  fmap f (Two x y) = Two x (f y)

instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
  arbitrary = do
    x <- arbitrary
    y <- arbitrary
    return $ Two x y

-- Possibly
data Possibly a = LolNope | Yeppers a deriving (Show, Eq)

instance Functor Possibly where
  fmap f LolNope     = LolNope
  fmap f (Yeppers a) = Yeppers $ f a

data Sum a b = First a | Second b deriving (Show, Eq)

instance Functor (Sum r) where
  fmap f (First x)  = First x
  fmap f (Second y) = Second $ f y

main :: IO ()
main = do
  print a
  print b
  print (c 1) 
  print (d 0)
  eres <- e
  print eres

  quickCheck (\x -> functorId (x :: [Int]))
  --quickCheck (functorCompTest :: [Int] -> (Fun Int String) -> (Fun String Char) -> Bool)
  
  print "Test functor laws for Identity:"
  quickCheck (functorId :: (Identity Int) -> Bool)
  quickCheck (functorComp :: Identity Int -> Fun Int Int -> Fun Int Int -> Bool)

  print "Test functor laws for Pair:"
  quickCheck (functorId :: (Pair Int) -> Bool)
  quickCheck (functorComp :: Pair Int -> Fun Int Char -> Fun Char Int -> Bool)

  print "Test functor laws for Two a:"
  quickCheck (functorId :: Two Int Char -> Bool)
  quickCheck (functorComp :: Two Int Char -> Fun Char String -> Fun String Int -> Bool)
