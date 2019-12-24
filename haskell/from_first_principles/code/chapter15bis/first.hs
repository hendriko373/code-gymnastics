import Test.QuickCheck

newtype First a = First (Maybe a)

instance Semigroup (First a) where
    (<>) (First Nothing) x = x
    (<>) x y = x

instance Monoid (First a) where
    mempty = (First Nothing)

