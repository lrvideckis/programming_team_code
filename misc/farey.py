//Farey sequence, grows n^2/3 with n
def farey_function(n, descending=False):
    """Print the nth Farey sequence, either ascending or descending."""
    a, b, c, d = 0, 1, 1, n
    if descending:
        a, c = 1, n-1
    print "%d/%d" % (a,b)
    while (c <= n and not descending) or (a > 0 and descending):
        k = int((n + b) / d)
        a, b, c, d = c, d, (k*c-a), (k*d-b)
print "%d/%d" % (a,b)
