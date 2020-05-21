module Lists where

import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

data List a = 
    Nil
  | Cons a (List a)
  deriving (Eq, Show)

instance Foldable List where
    foldr _ b Nil         = b  
    foldr f b (Cons a as) = f a (foldr f b as)

instance Functor List where
    fmap f Nil         = Nil
    fmap f (Cons x xs) = Cons (f x) (fmap f xs)

instance Applicative List where
    pure x = Cons x Nil
    (<*>) = go where
        go Nil xs = Nil
        go (Cons f fs) xs = append (fmap f xs) (go fs xs)  

instance Arbitrary a => Arbitrary (List a) where
    arbitrary = do
        l <- arbitrary
        return $ toList l

append :: List a -> List a -> List a
append Nil ys = ys
append (Cons x xs) ys = Cons x (append xs ys)

concat :: List (List a) -> List a
concat = foldr append Nil

take' :: Int -> List a -> List a
take' n Nil = Nil
take' n (Cons x xs) 
    | n <= 0 = Nil
    | otherwise = Cons x $ take' (n - 1) xs

newtype ZipList a =
    ZipList (List a)
  deriving (Eq, Show)

instance Functor ZipList where
    fmap f (ZipList l) = ZipList (fmap f l)

instance Applicative ZipList where
    pure x = ZipList $ toList $ repeat x
    (<*>) (ZipList fs) (ZipList xs) = ZipList $ go fs xs where
        go Nil x = Nil
        go x Nil = Nil
        go (Cons f fs) (Cons x xs) =
            Cons (f x) $ go fs xs

instance Eq a => EqProp (ZipList a) where
    xs =-= ys = xs' `eq` ys' where 
        xs' = let (ZipList l) = xs
              in take' 3000 l
        ys' = let (ZipList l) = ys
              in take' 3000 l

toList :: [a] -> List a
toList = foldr Cons Nil

instance Arbitrary a => Arbitrary (ZipList a) where
    arbitrary = do
        l <- arbitrary
        return $ ZipList $ toList l

data Validation e a =
    F e
  | S a
  deriving (Eq, Show)

instance Functor (Validation e) where
    fmap f (F e) = F e
    fmap f (S a) = S $ f a

instance Monoid e => Applicative (Validation e) where
    pure = S
    S f <*> S a = S $ f a 
    S f <*> F e = F e
    F e <*> S a = F e
    F e1 <*> F e2 = F $ e1 <> e2

instance (Arbitrary a, Arbitrary e) => Arbitrary (Validation e a) where
    arbitrary = do
        e <- arbitrary
        a <- arbitrary
        frequency [(1, return $ F e), (1, return $ S a)]

instance (Eq e, Eq a) => EqProp (Validation e a) where
    (=-=) = eq

test = quickBatch $ applicative $ ZipList $ Cons ("b", "w", 1::Integer) Nil
testVal = quickBatch $ applicative (undefined :: Validation [String] (String, String, Int))