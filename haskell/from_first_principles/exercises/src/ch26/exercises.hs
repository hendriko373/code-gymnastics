import Control.Monad.Trans.Reader
import Control.Monad.Trans.State
import Control.Monad.Identity
import Control.Monad.Trans.Maybe
import Control.Monad
import Control.Monad.Trans.Class

-- 1
rDec :: Num a => Reader a a
rDec = reader $ \r -> r - 1 

-- 2
rDec' :: Num a => Reader a a
rDec' = reader $ subtract 1 

-- 3
rShow :: Show a => ReaderT a Identity String
rShow = ReaderT $ \r -> Identity (show r)

-- 4
rShow' :: Show a => ReaderT a Identity String
rShow' = ReaderT $ Identity . show

-- 5
rPrintAndInc :: (Num a, Show a) => ReaderT a IO a
rPrintAndInc = ReaderT $ \r -> do
    putStrLn $ "Hi: " ++ show r
    return $ r + 1

-- 6
sPrintIncAccum :: (Num a, Show a) => StateT a IO String
sPrintIncAccum = StateT $ \s -> do
    putStrLn $ "Hi: " ++ show s
    return (show s, s + 1)


-- Excite
isValid :: String -> Bool
isValid v = '!' `elem` v

maybeExcite :: MaybeT IO String
maybeExcite = do
    v <- lift getLine
    guard $ isValid v
    return v

doExcite :: IO ()
doExcite = do
    putStrLn "say something excite!"
    excite <- runMaybeT maybeExcite
    case excite of
        Nothing -> putStrLn "MOAR EXCITE"
        Just e -> putStrLn ("Good, was very excite: " ++ e)

