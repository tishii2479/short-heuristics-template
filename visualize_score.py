import matplotlib.pyplot as plt

with open("./score.log", "r") as f:
    scores = list(map(int, f.readline().split()))

plt.plot(scores)
plt.show()
