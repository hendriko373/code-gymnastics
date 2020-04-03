import Control.Monad
import Control.Monad.Trans.State
import Data.Foldable

newtype Moi s a =
    Moi { runMoi :: s -> (a, s) }

instance Functor (Moi s) where
    fmap f g = Moi $ h . runMoi g where
        h (a, s) = (f a, s)

instance Applicative (Moi s) where
    pure a = Moi $ \s -> (a, s)
    Moi f <*> Moi g = Moi $ \s -> 
        let (f', s') = f s 
            (a, s'') = g s'
         in (f' a, s'')

instance Monad (Moi s) where
    return = pure
    f >>= g = Moi $ \s ->
        let (a, s') = runMoi f s
         in runMoi (g a) s'

-- The State applicative is implemented via <*> = Control.Monad.ap, whose
-- definition in base is copied here (and renamed to avoid conflicts):
app                :: (Monad m) => m (a -> b) -> m a -> m b
app m1 m2          = do { x1 <- m1; x2 <- m2; return (x1 x2) }

-- Specialized for Moi s this translates in
appMoi :: Moi s (a -> b) -> Moi s a -> Moi s b
appMoi f1 f2 = do
    x1 <- f1
    x2 <- f2
    return $ x1 x2

-- Desugaring the do syntax we get
applight :: Monad m => m (a -> b) -> m a -> m b
applight f1 f2 = 
    f1 >>= (\x1 ->
        f2 >>= (\x2 -> return $ x1 x2))

-- This clearly reduces to the definition above. Note especially that the
-- intermediate state s1 in (a1, s1) = runState f1 s0 is passed on to the second
-- state processor f2.

-- The bind method shows the true intent of the State type. In f1 >>= f2, f1
-- wraps a function of type s -> (a, s), whereas f2 wrap a type a -> s -> (a,
-- s), which is the curried version of (a, s) -> (a, s) clearly showing that we
-- are composing two functions and passing on an updated state. The bind method
-- hence is composition + transforming and passing on a state object.
--
-- Compare this with the Reader monad, which also allows us to compose two
-- functions but passes on a read only object to the composed functions.

-- FizzBuzzList
fizzBuzz :: Integer -> String
fizzBuzz n | n `mod` 15 == 0 = "FizzBuzz"
           | n `mod` 5  == 0 = "Fizz"
           | n `mod` 3  == 0 = "Buzz"
           | otherwise       = show n

addResult :: Integer -> State [String] ()
addResult n = do
    xs <- Control.Monad.Trans.State.get
    let result = fizzBuzz n
    Control.Monad.Trans.State.put (result : xs)

fizzBuzzList :: Integer -> Integer -> [String]
fizzBuzzList s e = execState (traverse_ addResult $ reverse [s..e]) []

-- traverese_ addResult (i:is) = flip const <$> addResult i <*> ...

-- Chapter exercises
get :: Moi s s
get = Moi $ \s -> (s, s)

put :: s -> Moi s ()
put s = Moi $ \_ -> ((), s) 

exec :: Moi s a -> s -> s
exec m = (snd . runMoi m) 

eval :: Moi s a -> s -> a
eval m = (fst . runMoi m) 

modify :: (s -> s) -> Moi s ()
modify f = Moi $ \s -> ((), f s)

