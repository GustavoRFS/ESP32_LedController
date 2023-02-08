import GitHubApi from "./gitHubApi";
import EspApi from "./espApi";

type updateResponse = {
  body: string;
  assets: {
    name: string;
  }[];
}[];

export const getUpdates = async () => {
  const release =
    localStorage.getItem("githubRelease") &&
    JSON.parse(localStorage.getItem("githubRelease"));

  if (
    release &&
    new Date(release.date).getTime() + 86400000 < new Date().getTime()
  )
    return release.data;

  localStorage.removeItem("githubRelease");

  const { data } = await GitHubApi.get<updateResponse>("/releases");

  localStorage.setItem(
    "githubRelease",
    JSON.stringify({ data, date: new Date() })
  );

  return data;
};

export const hasUpdates = async () => {
  try {
    await EspApi.get("/has-updates");
  } catch (error) {
    return false;
  }

  return true;
};

export const startUpdate = async () => {
  try {
    await EspApi.post("/update");
  } catch (error) {
    return false;
  }

  return true;
};
