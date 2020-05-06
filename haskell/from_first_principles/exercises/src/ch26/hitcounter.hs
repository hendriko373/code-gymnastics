{-# LANGUAGE OverloadedStrings #-}

module Main where

import Control.Monad.Trans.Class
import Control.Monad.Trans.Reader
import Control.Monad.Trans.State.Lazy (runState)
import Data.IORef
import qualified Data.Map as M
import Data.Maybe (fromMaybe)
import Data.Text.Lazy (Text)
import Data.String
import qualified Data.Text.Lazy as TL
import System.Environment (getArgs)
import Web.Scotty.Trans
import Web.Scotty.Internal.Types
import Control.Monad.IO.Unlift

data Config =
    Config {
        -- that's one, one click!
        -- two...two clicks!
        -- Three BEAUTIFUL clicks! ah ah ahhhh
        counts :: IORef (M.Map Text Integer)
      , prefix :: Text
      }

-- Stuff inside ScottyT is, except for things that escape
-- via IO, effectively read-only so we can't use StateT.
-- It would overcomplicate things to attempt to do so and
-- you should be using a proper database for production
-- applications.
type Scotty = ScottyT Text (ReaderT Config IO)
type Handler = ActionT Text (ReaderT Config IO)

bumpBoomp :: Text
    -> M.Map Text Integer
    -> (M.Map Text Integer, Integer)
bumpBoomp k m = let c = M.findWithDefault 0 k m
                 in (M.insert k (c+1) m, c+1)

app :: Scotty ()
app =
    get "/:key" $ do
        unprefixed <- param "key"
        Config cnts pre <- lift ask
        let key' = mappend pre unprefixed
            map' = readIORef cnts
        (newMap, newInteger) <- liftIO $ bumpBoomp key' <$> map'
        liftIO $ writeIORef cnts newMap
        html $ mconcat [ "<h1>Success! Count was: "
                   , TL.pack $ show newInteger
                   , "</h1>"
                   ]

main :: IO ()
main = do
    [prefixArg] <- getArgs
    counter <- newIORef (M.empty :: M.Map Text Integer)
    let config = Config counter $ fromString prefixArg
        runR   = \r -> runReaderT r config
    scottyT 3000 runR app
