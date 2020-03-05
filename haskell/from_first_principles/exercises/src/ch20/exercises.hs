module Ex20 where

import Data.Semigroup
import Data.Monoid

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