
#vnc image for GUI
FROM gitpod/workspace-full-vnc:latest

USER gitpod

# Install wxwidgets libs
RUN sudo apt-get update && \
    sudo install-packages libgtk-3-dev libwxgtk3.0-gtk3-0v5 libwxgtk3.0-gtk3-dev