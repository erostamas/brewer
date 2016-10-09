# Start from debain base image
FROM debian:latest

# Install vim
RUN apt-get update && apt-get upgrade && apt-get install -y vim

# Install build-essential
RUN apt-get install -y build-essential


