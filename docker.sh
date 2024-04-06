#!/bin/sh

# Delete existing installations
sudo apt-get remove docker docker-engine docker.io containerd runc

# Set up repos
sudo apt-get update
sudo apt-get install \
    ca-certificates \
    curl \
    gnupg \
    lsb-release

sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update

# Install docker engine
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin

# Add yourself to group
sudo usermod -aG docker $USER

echo "Please log out and back in for changes to take effect.  Then, run the following"
echo "commands to test your installation:"
cat << EOF
docker run hello-world
EOF