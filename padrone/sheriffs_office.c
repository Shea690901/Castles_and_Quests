wanted(bandit, crime, reward)
{
    write("(Warning: Called wanted in old room. This should be changed.)\n");
    return call_other("players/padrone/inside/sheriffs_office", "wanted", bandit, crime, reward);
}
