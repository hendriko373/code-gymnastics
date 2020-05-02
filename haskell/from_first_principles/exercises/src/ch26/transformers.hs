import Control.Monad.Trans.Class
import Control.Monad.IO.Class
import Control.Monad.Identity

-- MaybeT
newtype MaybeT m a =
    MaybeT { runMaybeT :: m (Maybe a) }

instance Functor m => Functor (MaybeT m) where
    fmap f (MaybeT ma) = MaybeT $ (fmap . fmap) f ma

instance Applicative m => Applicative (MaybeT m) where
    pure x = MaybeT $ (pure . pure) x
    (MaybeT mab) <*> (MaybeT ma) =
        MaybeT $ (<*>) <$> mab <*> ma 

instance Monad m => Monad (MaybeT m) where
    return = pure
    (MaybeT ma) >>= f = MaybeT $ do
        v <- ma
        case v of
          Nothing -> return Nothing
          Just y  -> (runMaybeT . f) y

instance MonadTrans MaybeT where
    lift = MaybeT . fmap Just

instance MonadIO m => MonadIO (MaybeT m) where
    liftIO = lift . liftIO

-- EitherT
newtype EitherT e m a =
    EitherT { runEitherT :: m (Either e a) }

instance Functor m => Functor (EitherT e m) where
    fmap f (EitherT ma) = EitherT $ (fmap . fmap) f ma

instance Applicative m => Applicative (EitherT e m) where
    pure = EitherT . pure . pure
    (EitherT mab) <*> (EitherT ma) = EitherT $
        (<*>) <$> mab <*> ma

instance Monad m => Monad (EitherT e m) where
    return = pure
    (EitherT ma) >>= f = EitherT $ do
        ea <- ma
        case ea of
          Left e  -> return $ Left e
          Right a -> (runEitherT . f) a 

instance MonadTrans (EitherT e) where
    lift = EitherT . fmap Right

instance MonadIO m => MonadIO (EitherT e m) where
    liftIO = lift . liftIO

swapEither :: Either a b -> Either b a
swapEither (Left a) = Right a
swapEither (Right b) = Left b

swapEitherT :: (Functor m) => EitherT e m a -> EitherT a m e
swapEitherT (EitherT ma) = EitherT $ swapEither <$> ma

eitherT :: Monad m =>
    (a -> m c)
    -> (b -> m c)
    -> EitherT a m b
    -> m c
eitherT amc bmc (EitherT mb) = do
    eab <- mb
    case eab of
      Left  a -> amc a
      Right b -> bmc b

-- ReaderT
newtype ReaderT r m a =
    ReaderT { runReaderT :: r -> m a }

instance Functor m => Functor (ReaderT r m) where
    fmap f (ReaderT rma) = ReaderT $ (fmap . fmap) f rma

instance Applicative m => Applicative (ReaderT r m) where
    pure = ReaderT . pure . pure
    (ReaderT rmab) <*> (ReaderT rma) = ReaderT $ 
        (<*>) <$> rmab <*> rma

instance Monad m => Monad (ReaderT r m) where
    return = pure
    (ReaderT rma) >>= armb = ReaderT $ \r ->
        rma r >>= flip (runReaderT . armb) r 
    
-- StateT
newtype StateT s m a =
    StateT { runStateT :: s -> m (a, s) }

instance Functor m => Functor (StateT s m) where
    fmap f (StateT sma) = StateT $ (fmap . fmap) h sma
        where h (a, s) = (f a, s)

instance Monad m => Applicative (StateT s m) where
    pure a = StateT $ \s -> pure (a, s)
    (StateT smab) <*> (StateT sma) = StateT $ \s -> do
        (ab, s') <- smab s
        (a, s'') <- sma s'
        return (ab a, s'')

instance Monad m => Monad (StateT s m) where
    return = pure
    (StateT sma) >>= f = StateT $ \s -> do
        (a, s') <- sma s
        (runStateT . f) a s'

instance MonadTrans (StateT s) where
    lift ma = StateT $ \s -> ma >>= (\a -> return (a, s))

instance MonadIO m => MonadIO (StateT s m) where
    liftIO = lift . liftIO

-- Monad commutativity
readerMaybe :: ReaderT r (MaybeT Identity) a -> r -> Maybe a
readerMaybe = (runIdentity . runMaybeT <$>) . runReaderT

maybeReader :: MaybeT (ReaderT r Identity) a -> r -> Maybe a
maybeReader = (runIdentity <$>) . runReaderT . runMaybeT
-- -> commuting

stateMaybe :: StateT s (MaybeT Identity) a -> s -> Maybe (a , s)
stateMaybe = (runIdentity . runMaybeT <$>) . runStateT

maybeState :: MaybeT (StateT s Identity) a -> s -> (Maybe a, s)
maybeState = (runIdentity <$>) . runStateT . runMaybeT
-- -> not commuting
