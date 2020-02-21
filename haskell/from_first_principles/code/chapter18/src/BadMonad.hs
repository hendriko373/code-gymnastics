module BadMonad where

import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

data Count a =
    Count Integer a
    deriving (Eq, Show)

instance Functor Count where
    fmap f (Count n a) = Count (n + 1) $ f a

instance Applicative Count where
    pure = Count 0
    (Count n f) <*> (Count n' a) = Count (n + n') $ f a

instance Monad Count where
    Count n a >>= f = 
        Count (n + 1) b where
            Count _ b = f a

-- RI not respected
--   Count n a >>= return =
--      Count (n + 1) a 
--      != Count n a
--
-- LI not respected
--   Count 0 a >>= f =
--      Count 1 b where Count _ b = f a
--      != Count 0 b

--instance Arbitrary a => Arbitrary (Count a) where
--    arbitrary = 
