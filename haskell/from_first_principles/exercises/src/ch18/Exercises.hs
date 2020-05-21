module Exercises where

import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

-- 1
data Nope a = NopeDotJpg
    deriving (Eq, Show)

instance Functor Nope where
    fmap _ _ = NopeDotJpg

instance Applicative Nope where
    pure _ = NopeDotJpg
    _ <*> _ = NopeDotJpg

instance Monad Nope where
    _ >>= _ = NopeDotJpg

instance EqProp (Nope a) where
    (=-=) = eq

instance Arbitrary (Nope a) where
    arbitrary = return NopeDotJpg

testNope = quickBatch (monad (undefined :: Nope (String, String, Int)))

-- 2
data Either' b a =
    Left' a
  | Right' b
  deriving (Eq, Show)

instance Functor (Either' b) where
    fmap _ (Right' b) = Right' b
    fmap f (Left' a) = Left' $ f a

instance Applicative (Either' b) where
    pure = Left'
    (Right' b) <*> _ = Right' b
    (Left' _) <*> (Right' b) = Right' b
    (Left' f) <*> (Left' a) = Left' $ f a

instance Monad (Either' b) where
    (Right' b) >>= _ = (Right' b)
    (Left' a)  >>= f = f a

instance (Eq a, Eq b) => EqProp (Either' b a) where
    (=-=) = eq

instance (Arbitrary a, Arbitrary b) => Arbitrary (Either' b a) where
    arbitrary = do
        a <- arbitrary
        b <- arbitrary
        frequency [(1, return $ Left' a), (1, return $ Right' b)]

testEither' = quickBatch $ monad (undefined :: Either String (String, String, Int))

--4
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

instance Monad List where
    Nil >>= f         = Nil
    (Cons a as) >>= f = append (f a) (as >>= f)

toList :: [a] -> List a
toList = foldr Cons Nil

append :: List a -> List a -> List a
append Nil ys = ys
append (Cons x xs) ys = Cons x (append xs ys)

instance Arbitrary a => Arbitrary (List a) where
    arbitrary = do
        l <- arbitrary
        return $ toList l

instance Eq a => EqProp (List a) where
    (=-=) = eq

testList = quickBatch $ monad (undefined :: List (String, String, Int))

--1
j :: Monad m => m (m a) -> m a
j m = m >>= id

--2
l1 :: Monad m => (a -> b) -> m a -> m b
l1 = fmap

--3
l2 :: Monad m => (a -> b -> c) -> m a -> m b -> m c
l2 f ma mb = f <$> ma <*> mb

--4
a :: Monad m => m a -> m (a -> b) -> m b
a = flip (<*>)

--5
meh :: Monad m => [a] -> (a -> m b) -> m [b]
meh []     _ = return mempty
meh (a:as) f = mappend <$> (return <$> f a) <*> (meh as f)

--6
flipType :: Monad m => [m a] -> m [a]
flipType = (flip meh) id

