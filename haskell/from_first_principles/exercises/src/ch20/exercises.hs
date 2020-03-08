module Ex20 where

import Data.Semigroup
import Data.Monoid

-- Library function

sum :: (Foldable t, Num a) => t a -> a
sum = getSum . foldMap Sum

product :: (Foldable t, Num a) => t a -> a
product = getProduct . foldMap Product

elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem a = getAny . foldMap (Any . ((==) a))

minimum :: (Foldable t, Ord a) => t a -> Maybe a
minimum f = foldr (min . Just) (Ex20.maximum f) f

maximum :: (Foldable t, Ord a) => t a -> Maybe a
maximum = foldr (max . Just) Nothing

minimum2 :: (Foldable t, Ord a, Bounded a) => t a -> a
minimum2 = getMin . foldMap Min

null :: (Foldable t) => t a -> Bool
null = foldr (\_ _ -> False) True

length :: (Foldable t) => t a -> Int
length = foldr (\_ -> (+1)) 0

toList :: (Foldable t) => t a -> [a]
toList = foldr ((:) . id) []

fold :: (Foldable t, Monoid m) => t m -> m
fold = foldMap id

myFoldMap :: (Foldable t, Monoid m) => (a -> m) -> t a -> m
myFoldMap f = foldr (mappend . f)  mempty

-- Exercises

data Constant a b =
    Constant a

instance Foldable (Constant a) where
    foldMap _ c = mempty 

data Two a b =
    Two a b

instance Foldable (Two a) where
    foldMap f (Two _ b) = f b

data Three a b c = 
    Three a b c

instance Foldable (Three a b) where
    foldMap f (Three _ _ c) = f c

data Three' a b = 
    Three' a b b

instance Foldable (Three' a) where
    foldMap f (Three' _ b1 b2) = f b1 <> f b2

filterF :: (Applicative f, Foldable t, Monoid (f a))
        => (a -> Bool) -> t a -> f a
filterF g = foldMap (\a -> if g a then pure a else mempty)
    