newtype Identity a =
    Identity { runIdentity :: a}
    deriving (Eq, Show)

newtype Compose f g a =
    Compose { getCompose :: f (g a) }
    deriving (Eq, Show)
    
instance Functor Identity where
    fmap f (Identity a) = Identity $ f a

instance (Functor f, Functor g) =>
         Functor (Compose f g) where
             fmap h (Compose fga) = 
                 Compose $ (fmap . fmap) h fga

instance (Applicative f, Applicative g) =>
    Applicative (Compose f g) where
        pure = Compose . pure . pure
        (<*>) (Compose fgab) (Compose fga) =
            Compose $ (<*>) <$> fgab <*> fga

instance (Foldable f, Foldable g) =>
    Foldable (Compose f g) where
        foldMap am (Compose fga) =
            foldMap (foldMap am) fga
            
instance (Traversable f, Traversable g) =>
    Traversable (Compose f g) where
        traverse ahb (Compose fga) =
            Compose <$> traverse (traverse ahb) fga

class Bifunctor p where
    {-# MINIMAL bimap | first, second #-}
    bimap :: (a -> b) -> (c -> d) -> p a c -> p b d
    bimap f g = first f . second g
    first :: (a -> b) -> p a c -> p b c
    first f = bimap f id
    second :: (b -> c) -> p a b -> p a c
    second = bimap id

data Deux a b = Deux a b
    deriving (Eq, Show)

instance Bifunctor Deux where
    bimap f g (Deux a b) = Deux (f a) (g b)

data Const a b = Const a
    deriving (Eq, Show)

instance Bifunctor Const where
    bimap f _ (Const a) = Const (f a)

