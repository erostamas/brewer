# brewer
# readme

# Installing docker on raspberry pi and building build image for brewer
curl -sSL https://get.docker.com | sh
sudo systemctl enable docker
sudo systemctl start docker
sudo usermod -aG docker brewer
sudo docker build -t brewer_build_image <path_to_dockerfile_in_repo>

