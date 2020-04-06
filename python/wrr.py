# Weighted round robin

def deadlines(loads, priors):
    """
    Calculates sensible deadlines for a set work items based on weighted round
    robin. Deadlines are estimated by the time an event should be finished if
    using weighted round robin to schedule the incoming loads.
    """
    result = [0] * len(loads)
    deadlines = [0] * len(loads)

    time = 0
    while any (l > 0 for l in loads):
        normal = normalized (pushforward (priors, loads))
        step = min ([t[0] / t[1] \
            for t in list (filter (lambda t: t[1] > 0, zip (loads, normal)))])
        deadlines = [t[0] + step if t[1] > 0 else t[0] for t in zip(deadlines, loads)]
        loads = [t[0] - t[1] * step if t[0] > 0 else t[0] for t in zip(loads, normal)]

    return [round (d, 0) for d in deadlines]

def pushforward(priors, loads):
    return [t[1] if t[0] > 0  else 0 for t in zip(loads, priors)]

def normalized(priors):
    return [p / sum(priors) for p in priors]

def is_finished(done, load):
    return done >= load
