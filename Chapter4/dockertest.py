import numpy as np
from matplotlib import pyplot

# Create test data
data = np.ones((10, 10))
data += np.random.normal(0, 0.1, data.shape)

# Plot the data
pyplot.imshow(data, cmap="gray")

# Save figure
pyplot.savefig("test.png")