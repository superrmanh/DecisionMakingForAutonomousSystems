# ROS 2 Humble development image for SSY236 Assignment 1
FROM osrf/ros:humble-desktop

ARG USERNAME=ros
ARG USER_UID=1000
ARG USER_GID=1000

ENV DEBIAN_FRONTEND=noninteractive \
    ROS_DISTRO=humble \
    LANG=C.UTF-8 \
    LC_ALL=C.UTF-8

RUN apt-get update && apt-get install -y --no-install-recommends \
        sudo bash-completion git vim nano gdb less \
        python3-colcon-common-extensions python3-rosdep python3-pip \
        mesa-utils libgl1-mesa-dri \
        ros-humble-rqt-graph ros-humble-rqt-topic \
    && rm -rf /var/lib/apt/lists/*

# Non-root user matching the host UID/GID so files written to the mounted
# workspace stay owned by you on the host.
RUN if getent passwd ${USER_UID} >/dev/null; then userdel -r "$(getent passwd ${USER_UID} | cut -d: -f1)"; fi \
    && if ! getent group ${USER_GID} >/dev/null; then groupadd --gid ${USER_GID} ${USERNAME}; fi \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m -s /bin/bash ${USERNAME} \
    && usermod -aG video ${USERNAME} \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

RUN { \
      echo ''; \
      echo '# --- ROS 2 Humble ---'; \
      echo 'source /opt/ros/humble/setup.bash'; \
      echo 'source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash 2>/dev/null'; \
      echo 'if [ -f "$HOME/ssy236_ws/install/setup.bash" ]; then source "$HOME/ssy236_ws/install/setup.bash"; fi'; \
      echo 'cd "$HOME/ssy236_ws"'; \
      echo 'export PS1="(humble) $PS1"'; \
    } >> /home/${USERNAME}/.bashrc

USER ${USERNAME}
WORKDIR /home/${USERNAME}/ssy236_ws
CMD ["bash"]
