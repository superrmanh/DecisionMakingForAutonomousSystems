#!/usr/bin/env bash
# Open a shell in the ROS 2 Humble container for this workspace.
#   ./humble.sh            start (if needed) and open a shell
#   ./humble.sh build      rebuild the image
#   ./humble.sh down       stop and remove the container
# Run it again in another terminal to get a second shell in the same container.
set -euo pipefail
cd "$(dirname "$(readlink -f "$0")")/docker"

export HOST_UID="$(id -u)" HOST_GID="$(id -g)"
export XAUTHORITY="${XAUTHORITY:-$HOME/.Xauthority}"

case "${1:-shell}" in
  build) docker compose build ;;
  down)  docker compose down ;;
  shell)
    if [ -z "$(docker compose ps -q --status running humble 2>/dev/null)" ]; then
      docker compose up -d
    fi
    docker compose exec humble bash
    ;;
  *) echo "usage: $0 [shell|build|down]"; exit 1 ;;
esac
