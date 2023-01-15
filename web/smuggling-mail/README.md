# Smuggling Mail
Challenge description: `Join our waitlist and we'll let you know about apartment vacancies!`
<details>
    <summary>Contains vulnerability/exploit spoilers</summary>
    As heavily hinted to by the name, this challenge combines HTTP request smuggling with command injection functionality in the popular `mail` program.
    The request smuggling is made possible because of how certain versions of Varnish mishandle HTTP/2 connections that are proxied to the backend.
    The command injection is then triggered by using the `mail` utility's built-in tilde escape functionality to run a shell command included in the email's body content.
</details>

## For testers
The `smuggling-mail.tar.gz` file contains everything needed to run the challenge and test it locally.
The Docker container can be built and deployed using the provided `run.sh` script.

Specific vulnerability details and a script are available in the `solution` directory.
Please feel free to reach out to me with any questions, concerns, or feedback (`eddie` in the OSIRIS Discord or `eddie@osiris.cyber.nyu.edu`).
Thank you!

*Planning to update the styling/theme, but the functionality will remain the same so any testing should still apply.
